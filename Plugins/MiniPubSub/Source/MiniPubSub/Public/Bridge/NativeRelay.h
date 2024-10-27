#pragma once
#include "Mobile.h"
#include "PubSub/Watcher.h"

class FNativeRelay
{
private:
	TSharedPtr<FMobile> Mobile;
	TSharedPtr<FWatcher> Watcher;

	void OnReceiveFromNative(const FString& Info, const FString& Data) const;
	void OnWatch(const FMessage& Message) const;
	
public:
	FNativeRelay();
	~FNativeRelay();
	
};
