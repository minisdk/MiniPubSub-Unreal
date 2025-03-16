#include "PubSub/Publisher.h"

#include "PubSub/MessageManager.h"

void MiniPubSub::FPublisher::Publish(const FString& Key, const FPayload& Message) const
{

	FNodeInfo Info;
	Info.MessageOwnerId = GetId();
	Info.PublisherId = GetId();
	FMessage Request(Info, Key, Message.Json, "");
	FMessageManager::Get()->GetMediator().Broadcast(Request);
}

void MiniPubSub::FPublisher::Publish(const FString& Key, const FPayload& Message, FReceiveDelegate ReplyCallback) const
{
	FString ReplyKey = FString::Printf(TEXT("%s_id%d"), *Key, FIdCounter::GetNext());
	FMessageManager::Get()->GetMediator().RegisterInstant(FReceiver(-1, ReplyKey, ReplyCallback));
	
	FNodeInfo Info;
	Info.MessageOwnerId = GetId();
	Info.PublisherId = GetId();
	FMessage Request(Info, Key, Message.Json, ReplyKey);
	FMessageManager::Get()->GetMediator().Broadcast(Request);
}

void MiniPubSub::FPublisher::Reply(const FMessageInfo& ReceivedMessageInfo, const FPayload& Message) const
{
	FNodeInfo Info;
	Info.MessageOwnerId = GetId();
	Info.PublisherId = GetId();
	FMessage Request(Info, ReceivedMessageInfo.ReplyKey, Message.Json, "");
	FMessageManager::Get()->GetMediator().Broadcast(Request);
}
