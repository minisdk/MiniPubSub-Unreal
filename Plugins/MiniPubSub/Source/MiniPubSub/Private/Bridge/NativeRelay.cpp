#include "Bridge/NativeRelay.h"
#include "Bridge/MobileBridge.h"

void FNativeRelay::OnReceiveFromNative(const FString& Data) const
{
	Watcher->Publish(FMessage::ParseFrom(Data));
}

void FNativeRelay::OnWatch(TSharedPtr<const FMessage> Message) const
{
	Bridge->Send(Message->ToString());
}

FNativeRelay::FNativeRelay()
{
	Bridge = MakeShareable(new FMobileBridge());
	Watcher = MakeShareable(new FWatcher());
	Watcher->Watch(FReceiveDelegate::CreateRaw(this, &FNativeRelay::OnWatch));
	// Bridge->DelNativeTextHandle.BindRaw(this, &FNativeRelay::OnReceiveFromNative);
	Bridge->BindNative(FDelegate_Native_Text_Handler::CreateRaw(this, &FNativeRelay::OnReceiveFromNative));
}

FNativeRelay::~FNativeRelay()
{
	Watcher->Unwatch();
}
