#include "PubSub/Watcher.h"

#include "PubSub/MessageManager.h"

const int FWatcher::Id() const
{
	return Publisher.Id();
}

void FWatcher::Watch(const FReceiveDelegate& ReceiveDelegate)
{
	FMessageManager::Get()->GetMediator().Watch(FReceiver(Id(), "", ReceiveDelegate));
}

void FWatcher::Unwatch()
{
	FMessageManager::Get()->GetMediator().Unwatch(Id());
}

void FWatcher::Publish(const FMessage& Message) const
{
	Publisher.Publish(Message);
}
