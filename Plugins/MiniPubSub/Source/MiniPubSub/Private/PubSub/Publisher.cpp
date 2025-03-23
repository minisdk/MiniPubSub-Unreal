#include "PubSub/Publisher.h"

#include "PubSub/MessageManager.h"

void MiniPubSub::FPublisher::Publish(const FTopic& Topic, const FPayload& Message) const
{

	FNodeInfo Info;
	Info.MessageOwnerId = GetId();
	Info.PublisherId = GetId();
	FMessage Request(Info, Topic, DefaultTopic, Message.Json);
	FMessageManager::Get()->GetMediator().Broadcast(Request);
}

void MiniPubSub::FPublisher::Publish(const FTopic& Topic, const FPayload& Message, FReceiveDelegate ReplyCallback) const
{
	FString ReplyKey = FString::Printf(TEXT("%s_id%d"), *Topic.Key, FIdCounter::GetNext());
	FTopic ReplyTopic{ReplyKey, ESdkType::Game};
	FMessageManager::Get()->GetMediator().RegisterInstant(FReceiver(-1, ReplyKey, ESdkType::Game, ReplyCallback));
	
	FNodeInfo Info;
	Info.MessageOwnerId = GetId();
	Info.PublisherId = GetId();
	FMessage Request(Info, Topic, ReplyTopic, Message.Json);
	FMessageManager::Get()->GetMediator().Broadcast(Request);
}

void MiniPubSub::FPublisher::Reply(const FMessageInfo& ReceivedMessageInfo, const FPayload& Payload) const
{
	this->Publish(ReceivedMessageInfo.Topic, Payload);
}
