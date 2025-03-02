#include "Bridge/NativeRelay.h"
#include "Bridge/Mobile.h"
#include "PubSub/MessageManager.h"

void MiniPubSub::FNativeRelay::OnReceiveFromNative(const FString& Info, const FString& Data) const
{
	FRequestInfo Decoded;
	Decoded.FromJson(Info);
	UE_LOG(LogTemp, Display, TEXT("[Unreal] OnReceiveFromNative... decoded info key : %s"), *Decoded.Key)

	FNodeInfo NodeInfo(Decoded.NodeInfo.RequestOwnerId, Watcher->GetId());
	FRequest Request(FRequestInfo(NodeInfo, Decoded.Key, Decoded.ResponseKey), Data);
	FMessageManager::Get()->GetMediator().Broadcast(Request);
}

void MiniPubSub::FNativeRelay::OnWatch(const FRequest& Request) const
{
	FString InfoStr = Request.Info.ToJson();
	Mobile->Send(InfoStr, Request.Json);
}

MiniPubSub::FNativeRelay::~FNativeRelay()
{
	UE_LOG(LogTemp, Display, TEXT("FNativeRelay destroy"))
	Watcher->Unwatch();
}

void MiniPubSub::FNativeRelay::Initialize()
{
	UE_LOG(LogTemp, Display, TEXT("FNativeRelay create"))
	Watcher = MakeShareable(new FWatcher());
	Mobile = MakeShareable(new FMobile());
	Watcher->Watch(FReceiveDelegate::CreateRaw(this, &FNativeRelay::OnWatch));
	Mobile->BindNative(FDelegate_Native_Handler::CreateRaw(this, &FNativeRelay::OnReceiveFromNative));
}
