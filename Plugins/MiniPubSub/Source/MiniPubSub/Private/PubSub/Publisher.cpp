#include "PubSub/Publisher.h"

#include "PubSub/MessageManager.h"

void MiniPubSub::FPublisher::Publish(const FTopic& Topic, const FPayload& Payload) const
{

	FNodeInfo Info;
	Info.MessageOwnerId = GetId();
	Info.PublisherId = GetId();
	FMessage Message(Info, Topic, DefaultTopic, Payload.Json);
	FMessageManager::Get()->GetMediator().Broadcast(Message);
}

void MiniPubSub::FPublisher::Publish(const FTopic& Topic, const FPayload& Payload, FReceiveDelegate ReplyCallback) const
{
	FString ReplyKey = FString::Printf(TEXT("%s_id%d"), *Topic.Key, FIdCounter::GetNext());
	FTopic ReplyTopic{ReplyKey, ESdkType::Game};
	FMessageManager::Get()->GetMediator().RegisterInstant(FReceiver(-1, ReplyKey, ESdkType::Game, ReplyCallback));
	
	FNodeInfo Info;
	Info.MessageOwnerId = GetId();
	Info.PublisherId = GetId();
	FMessage Message(Info, Topic, ReplyTopic, Payload.Json);
	FMessageManager::Get()->GetMediator().Broadcast(Message);
}

void MiniPubSub::FPublisher::Reply(const FMessageInfo& ReceivedMessageInfo, const FPayload& Payload) const
{
	this->Publish(ReceivedMessageInfo.Topic, Payload);
}

MiniPubSub::FPayload MiniPubSub::FPublisher::SendSync(const FTopic& Topic, const FPayload& Payload) const
{
	FNodeInfo Info;
	Info.MessageOwnerId = GetId();
	Info.PublisherId = GetId();
	FMessage Message(Info, Topic, DefaultTopic, Payload.Json);
	return FMessageManager::Get()->GetMediator().SendSync(Message); 
}
