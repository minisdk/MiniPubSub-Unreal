#include "PubSub/Messenger.h"

#include "PubSub/MessageManager.h"


void MiniPubSub::FMessenger::Subscribe(const FString& Key, const FReceiveDelegate& ReceiveDelegate)
{
	FMessageManager::Get()->GetMediator().Register(FReceiver(GetId(), Key, ReceiveDelegate));
}

void MiniPubSub::FMessenger::Unsubscribe(const FString& Key)
{
	FMessageManager::Get()->GetMediator().Unregister(GetId(), Key);
}
