#pragma once
#include "Bridge/Mobile.h"
#include "PubSub/Watcher.h"

namespace MiniPubSub
{
	class FNativeRelay final
	{
	private:
		TSharedPtr<FMobile> Mobile;
		TSharedPtr<FWatcher> Watcher;

		void OnReceiveFromNative(const FString& Info, const FString& Data) const;
		void OnWatch(const FRequest& Request) const;
	
	public:
		~FNativeRelay();
		void Initialize();
	
	};
	
}
