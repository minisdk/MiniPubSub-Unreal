#include "PubSub/Publisher.h"

#include "PubSub/MessageManager.h"

void MiniPubSub::FPublisher::Publish(const FString& Key, const FMessage& Message) const
{

	FNodeInfo Info;
	Info.RequestOwnerId = GetId();
	Info.PublisherId = GetId();
	FRequest Request(Info, Key, Message.Json, "");
	FMessageManager::Get()->GetMediator().Broadcast(Request);
}

void MiniPubSub::FPublisher::Publish(const FString& Key, const FMessage& Message, FReceiveDelegate ResponseCallback)
{
	FString ResponseKey = FString::Printf(TEXT("%s_id%d"), *Key, FIdCounter::GetNext());
	
	FNodeInfo Info;
	Info.RequestOwnerId = GetId();
	Info.PublisherId = GetId();
	FRequest Request(Info, Key, Message.Json, "");
	FMessageManager::Get()->GetMediator().Broadcast(Request);
}

void MiniPubSub::FPublisher::Respond(const FResponseInfo& ResponseInfo, const FMessage& Message)
{
	FNodeInfo Info;
	Info.RequestOwnerId = GetId();
	Info.PublisherId = GetId();
	FRequest Request(Info, ResponseInfo.Key, Message.Json, "");
	FMessageManager::Get()->GetMediator().Broadcast(Request);
}
