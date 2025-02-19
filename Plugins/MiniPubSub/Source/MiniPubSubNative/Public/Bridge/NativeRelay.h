#pragma once
#include "Bridge/Mobile.h"
#include "Module/ModuleBase.h"
#include "PubSub/Watcher.h"

namespace MiniPubSub
{
	class FNativeRelay : public FModuleBase
	{
	private:
		TSharedPtr<FMobile> Mobile;
		TSharedPtr<FWatcher> Watcher;

		void OnReceiveFromNative(const FString& Info, const FString& Data) const;
		void OnWatch(const FRequest& Request) const;
	
	public:
		virtual ~FNativeRelay() override;
		virtual void Initialize() override;
	
	};
	
}
