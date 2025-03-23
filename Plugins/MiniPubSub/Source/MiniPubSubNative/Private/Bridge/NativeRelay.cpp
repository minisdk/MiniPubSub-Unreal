#include "Bridge/NativeRelay.h"
#include "Bridge/Mobile.h"
#include "PubSub/MessageManager.h"

void MiniPubSub::FNativeRelay::OnReceiveFromNative(const FString& Info, const FString& Data) const
{
	FMessageInfo Decoded;
	Decoded.FromJson(Info);
	UE_LOG(LogTemp, Display, TEXT("[Unreal] OnReceiveFromNative... decoded info key : %s"), *Decoded.Topic.Key)

	FNodeInfo NodeInfo(Decoded.NodeInfo.MessageOwnerId, Watcher->GetId());
	FMessage Message(FMessageInfo(NodeInfo, Decoded.Topic, Decoded.ReplyTopic), Data);
	FMessageManager::Get()->GetMediator().Broadcast(Message);
}

void MiniPubSub::FNativeRelay::OnWatch(const FMessage& Message) const
{
	FString InfoStr = Message.Info.ToJson();
	Mobile->Send(InfoStr, Message.Payload.Json);
}

MiniPubSub::FNativeRelay::~FNativeRelay()
{
	UE_LOG(LogTemp, Display, TEXT("FNativeRelay destroy"))
	Watcher->Unwatch();
}

void MiniPubSub::FNativeRelay::Initialize()
{
	UE_LOG(LogTemp, Display, TEXT("FNativeRelay create"))
	Watcher = MakeShared<FWatcher>(ESdkType::Native);
	Mobile = MakeShared<FMobile>();
	Watcher->Watch(FReceiveDelegate::CreateRaw(this, &FNativeRelay::OnWatch));
	Mobile->BindNative(FDelegate_Native_Handler::CreateRaw(this, &FNativeRelay::OnReceiveFromNative));
}
