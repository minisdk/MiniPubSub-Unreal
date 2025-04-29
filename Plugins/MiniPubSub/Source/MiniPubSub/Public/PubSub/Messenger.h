#pragma once
#include "Handler.h"
#include "Publisher.h"
#include "Receiver.h"

namespace MiniPubSub
{
	class MINIPUBSUB_API FMessenger final: public FPublisher
	{
		ESdkType Target;
	public:
		explicit FMessenger(const ESdkType InTarget = ESdkType::Game)
			: Target(InTarget){}
		void Subscribe(const FString& Key, const FReceiveDelegate& ReceiveDelegate);
		void Unsubscribe(const FString& Key);
		void Handle(const FString& Key, const FHandleDelegate& HandleDelegate);
	};

}
