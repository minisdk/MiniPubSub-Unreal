#include "PubSub/Watcher.h"

#include "PubSub/MessageManager.h"

const FString WatcherKey = TEXT("Key_Watcher_Reserved");

void MiniPubSub::FWatcher::Watch(const FReceiveDelegate& ReceiveDelegate)
{
	FMessageManager::Get()->GetMediator().Register(FReceiver(GetId(), WatcherKey, Target, ReceiveDelegate));
}

void MiniPubSub::FWatcher::Unwatch()
{
	FMessageManager::Get()->GetMediator().Unregister(GetId(), WatcherKey);
}
