#include "PubSub/Messenger.h"

#include "PubSub/MessageManager.h"

const int FMessenger::Id() const
{
	return this->Publisher.Id();
}

void FMessenger::Subscribe(const FString& Key, const FReceiveDelegate& ReceiveDelegate)
{
	FMessageManager::Get()->GetMediator().Register(FReceiver(Id(), Key, ReceiveDelegate));
}

void FMessenger::Unsubscribe(const FString& Key)
{
	FMessageManager::Get()->GetMediator().Unregister(Id(), Key);
}

void FMessenger::Publish(const FMessage& Message) const
{
	Publisher.Publish(Message);
}
