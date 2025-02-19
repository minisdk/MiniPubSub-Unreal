#pragma once
#include "Publisher.h"
#include "Receiver.h"

namespace  MiniPubSub
{
	class MINIPUBSUB_API FWatcher final : public FNode
	{
	public:
		void Watch(const FReceiveDelegate& ReceiveDelegate);
		void Unwatch();
	};
}
