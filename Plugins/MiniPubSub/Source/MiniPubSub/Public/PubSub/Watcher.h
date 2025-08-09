#pragma once
#include "Publisher.h"
#include "Receiver.h"

namespace  MiniPubSub
{
	class MINIPUBSUB_API FWatcher final : public FNode
	{
		ESdkType Target;
		
	public:
		explicit FWatcher(const ESdkType& InTarget = ESdkType::Game)
			: Target(InTarget){}
		void Watch(const FReceiveDelegate& ReceiveDelegate);
		void Unwatch();
	};
}
