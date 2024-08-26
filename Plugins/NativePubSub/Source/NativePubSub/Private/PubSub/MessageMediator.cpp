#include "PubSub/MessageMediator.h"

void FMessageMediator::Register(const FReceiver& Receiver)
{
	ReceiverDic.FindOrAdd(Receiver.Key).Add(Receiver);
	
}

void FMessageMediator::Unregister(const int& Id, const FString& Key)
{
	TArray<FReceiver>* Receivers = ReceiverDic.Find(Key);
	if(Receivers != nullptr)
	{
		Receivers->RemoveAll([Id](const FReceiver Receiver)
		{
			return Receiver.NodeId == Id;
		});
	}
}

void FMessageMediator::Watch(const FReceiver& Receiver)
{
	WatcherDic.Add(Receiver.NodeId, Receiver);
}

void FMessageMediator::Unwatch(const int& Id)
{
	WatcherDic.Remove(Id);
}

void FMessageMediator::Publish(TSharedPtr<const FMessage> Message, const int& PublisherId)
{
	if(Message.IsValid() == false)
		 return;
	if(TArray<FReceiver>* Receivers = ReceiverDic.Find(Message->Key))
	{
		for (FReceiver Receiver : *Receivers)
		{
			if(Receiver.NodeId == PublisherId)
				continue;
			bool _ = Receiver.ReceiveDelegate.ExecuteIfBound(Message);
		}
	}

	for (TTuple<int, FReceiver> Watcher : WatcherDic)
	{
		if(Watcher.Key == PublisherId)
			continue;
		bool _ = Watcher.Value.ReceiveDelegate.ExecuteIfBound(Message);
	}
}
