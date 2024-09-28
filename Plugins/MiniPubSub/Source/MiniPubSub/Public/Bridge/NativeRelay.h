#pragma once
#include "MobileBridge.h"
#include "PubSub/Watcher.h"

class FNativeRelay
{
private:
	TSharedPtr<FMobileBridge> Bridge;
	TSharedPtr<FWatcher> Watcher;

	void OnReceiveFromNative(const FString& Data) const;
	void OnWatch(TSharedPtr<const FMessage> Message) const;
	
public:
	FNativeRelay();
	~FNativeRelay();
	
};
