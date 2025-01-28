#include "Bridge/NativeRelay.h"
#include "Bridge/Mobile.h"

void FNativeRelay::OnReceiveFromNative(const FString& Info, const FString& Data) const
{
	FMessageInfo Decoded;
	FJsonObjectConverter::JsonObjectStringToUStruct(Info, &Decoded);
	UE_LOG(LogTemp, Display, TEXT("[Unreal] OnReceiveFromNative... decoded info key : %s"), *Decoded.Key)
	Watcher->Publish(FMessage(Decoded, Data));
}

void FNativeRelay::OnWatch(const FMessage& Message) const
{
	FString InfoStr;
	if(FJsonObjectConverter::UStructToJsonObjectString(Message.Info, InfoStr))
	{
		Mobile->Send(InfoStr, Message.Json);	
	}
	
}

FNativeRelay::~FNativeRelay()
{
	UE_LOG(LogTemp, Display, TEXT("FNativeRelay destroy"))
	Watcher->Unwatch();
}

void FNativeRelay::Initialize()
{
	FModuleBase::Initialize();
	
	UE_LOG(LogTemp, Display, TEXT("FNativeRelay create"))
	Watcher = MakeShareable(new FWatcher());
	Mobile = MakeShareable(new FMobile());
	Watcher->Watch(FReceiveDelegate::CreateRaw(this, &FNativeRelay::OnWatch));
	Mobile->BindNative(FDelegate_Native_Handler::CreateRaw(this, &FNativeRelay::OnReceiveFromNative));
}
