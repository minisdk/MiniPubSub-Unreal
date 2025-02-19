#pragma once
#include "Node.h"
#include "Receiver.h"
#include "Data/Message.h"
#include "Data/SdkType.h"

namespace MiniPubSub
{
	class MINIPUBSUB_API FPublisher : public FNode
	{
	public:
		virtual ~FPublisher() override = default;
		void Publish(const FString& Key, const FMessage& Message) const;
		void Publish(const FString& Key, const FMessage& Message, FReceiveDelegate ResponseCallback);
		void Respond(const FResponseInfo& ResponseInfo, const FMessage& Message);
	};

}
