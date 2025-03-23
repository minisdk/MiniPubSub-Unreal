#pragma once
#include "Node.h"
#include "Receiver.h"
#include "Data/Payload.h"
#include "Data/SdkType.h"

namespace MiniPubSub
{
	class MINIPUBSUB_API FPublisher : public FNode
	{
	public:
		virtual ~FPublisher() override = default;
		void Publish(const FTopic& Topic, const FPayload& Message) const;
		void Publish(const FTopic& Topic, const FPayload& Message, FReceiveDelegate ReplyCallback) const;
		void Reply(const FMessageInfo& ReceivedMessageInfo, const FPayload& Payload) const;
	};

}
