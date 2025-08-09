#include "PubSub/MessageManager.h"

TSharedPtr<MiniPubSub::FMessageManager> MiniPubSub::FMessageManager::Get()
{
	static TSharedPtr<FMessageManager> Instance;
	if(Instance == nullptr || !Instance.IsValid())
	{
		Instance = MakeShareable(new FMessageManager());
	}
	return Instance;
}

MiniPubSub::FMessageMediator& MiniPubSub::FMessageManager::GetMediator()
{
	return Mediator;
}

