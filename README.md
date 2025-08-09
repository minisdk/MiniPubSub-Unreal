# NativePubSub-Unreal
언리얼 엔진과 모바일 플랫폼간 통신을 위한 pubsub 방식의 라이브러리입니다.
직렬화된 데이터를 발행하여 사전 등록된 구독자들에게 전달합니다.

## 같이 보기
- [MiniPubSub-Android](https://github.com/minisdk/MiniPubSub-Android)
- [MiniPubSub-iOS](https://github.com/minisdk/MiniPubSub-iOS)
- [MiniPubSub-Unity](https://github.com/minisdk/MiniPubSub-Unity)

## 시작하기
[Release](https://github.com/minisdk/MiniPubSub-Unreal/releases) 에서 플러그인을 다운 받아 프로젝트에 추가합니다.

## 주요 요소들

### FPayload
데이터 저장 객체입니다.<br>
데이터를 json 시리얼라이즈한 형태로 저장합니다.<br>
데이터 직렬화 헬퍼 함수를 제공합니다.
- `FromJsonSerializable<typename DataType>(DataType Data)` : `FJsonSerializable` 상속 객체를 직렬화하여 저장합니다.
- `FromJsonObject(const TSharedRef<FJsonObject>& JsonObject)`: `TSharedRef<FJsonObject>` 객체 참조를 직렬화하여 저장합니다.

### FTopic
발행 데이터의 타입입니다.<br>
어느 플랫폼(Game or Native) 의 어느 구독자에게 전달할지 결정합니다.

### FMessageInfo
발행 데이터의 메타데이터입니다.<br>
해당 발행 데이터의 발행자, 목적지(`FTopic`) 같은 데이터 전달에 필요한 정보를 담고 있습니다.

### FMessage
`FPayload`와 `FMessageInfo` 객체를 포함한 데이터 전달 객체입니다.<br>
- `GetKey()` : 발행자와 구독자 사이에 약속한 발행 데이터 식별자입니다.<br>
발행자가 특정 키로 `Topic`을 생성해서 메세지를 발행하면, 사전에 해당 키를 구독한 구독자가 메세지를 받습니다.
- `ToJsonSerializable<typename DataType>()` : 역직렬화한 `FJsonSerializable` 상속 객체를 반환합니다.
- `ToJsonObject()` : 역직렬화한 `TSharedPtr<FJsonObject>` 를 리턴합니다.

### FMessenger
`FMessage` 객체를 발행(`Publish`) 하거나 구독(`Subscribe`)합니다.<br>
또한 동기적으로 `FMessage` 객체를 보내고(`SendSync`) 처리(`Handle`) 하여 반환합니다.<br><br>
데이터는 크게 세가지 방법으로 주고 받을 수 있습니다.
- pub/sub
  - 기본적인 발행/구독 방식. 구독자가 `Subscribe` 하고 발행자가 `Publish` 하여 `FMessage`를 주고 받습니다. 
- pub/sub and reply
  - 구독자가 다시 발행자에게 `FMessage`를 비동기적으로 전달(`Reply`)합니다.
- sendSync/handle
  - 발행자가 동기적으로 `FMessage`를 전달(`SendSync`)하고 사전에 처리(`Handle`) 하기로 한 구독자가 그 결과(`FPayload`) 를 반환합니다.
 
## 예제 코드
```cpp
// .h
class FMyController
{
    MiniPubSub::FMessenger Messenger;

    void OnWorld(const MiniPubSub::FMessage& Message);
    void OnHelloReplyMode(const MiniPubSub::FMessage& Message);
public:
    MyController();
    void Hello();
    void HelloReplyMode();
    void HelloSync();
}

// .cpp
namespace
{
    constexpr TCHAR KEY_PUB_HELLO[] = TEXT("SAMPLE::HELLO");
    constexpr TCHAR KEY_SUB_WORLD[] = TEXT("SAMPLE::WORLD");
    constexpr TCHAR KEY_PUB_HELLO_REPLY_MODE[] = TEXT("SAMPLE::HELLO_REPLY");
    constexpr TCHAR KEY_SYNC_SEND[] = TEXT("SAMPLE::SYNCSEND");
}

FMyController::FMyController()
: Messenger(MiniPubSub::FMessenger())
{
    Messenger.Subscribe(KEY_SUB_WORLD, MiniPubSub::FReceiveDelegate::CreateRaw(this, &FMyController::OnWorld));
}

FMyController::OnWorld(const FMessage& Message)
{
    FMyWorldData Data = Message.ToJsonSerializable<FMyWorldData>();
    // Do Something...
}

void FMyController::Hello()
{
    Messenger.Publish(
        MiniPubSub::FTopic(KEY_PUB_HELLO, MiniPubSub::ESdkType::Native),
        MiniPubSub::FPayload::FromJsonSerializable(FMyHelloData())
    );
}

void FMyController::HelloReplyMode()
{
    Messenger.Publish(
        MiniPubSub::FTopic(KEY_PUB_HELLO_REPLY_MODE, MiniPubSub::ESdkType::Native),
        MiniPubSub::FPayload::FromJsonSerializable(FMyHelloData()),
        MiniPubSub::FReceiveDelegate::CreateLambda(
            [](const MiniPubSub::FMessage& Message)
            {
                FMyWorldData = Message.ToJsonSerializable<FMyWorldData>();
            }
        )
    );
}

void FMyController::HelloSync()
{
    MiniPubSub::FPayload Result = Messenger.SendSync(
        MiniPubSub::FTopic(KEY_SYNC_SEND, MiniPubSub::ESdkType::Native),
        MiniPubSub::FPayload::FromJsonSerializable(FMySyncData())
    );
    FMySyncResult MyResult = Result.ToJsonSerializable<FMySyncResult>();
}
```
