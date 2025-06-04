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
		void Publish(const FTopic& Topic) const;
		void Publish(const FTopic& Topic, const FReceiveDelegate& ReplyCallback) const;
		void Publish(const FTopic& Topic, const FPayload& Payload) const;
		void Publish(const FTopic& Topic, const FPayload& Payload, const FReceiveDelegate& ReplyCallback) const;
		void Reply(const FMessageInfo& ReceivedMessageInfo, const FPayload& Payload) const;
		FPayload SendSync(const FTopic& Topic, const FPayload& Payload) const;
	};

}
