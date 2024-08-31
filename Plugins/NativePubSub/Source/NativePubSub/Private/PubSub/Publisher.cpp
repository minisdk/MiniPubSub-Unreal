#include "PubSub/Publisher.h"

#include "PubSub/MessageManager.h"

static int GetId()
{
	static int Id = static_cast<int>(EPublisherType::Game);
	return ++Id;
}

FPublisher::FPublisher()
:NodeId(GetId())
{}

FPublisher::~FPublisher()
{
}

void FPublisher::Publish(TSharedPtr<const FMessage> Message) const
{
	FMessageManager::Get()->GetMediator().Publish(Message, Id());
}
