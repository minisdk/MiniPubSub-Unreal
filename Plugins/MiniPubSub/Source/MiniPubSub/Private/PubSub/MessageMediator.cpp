#include "PubSub/MessageMediator.h"

void MiniPubSub::FMessageMediator::Register(const FReceiver& Receiver)
{
	ReceiverMap.FindOrAdd(Receiver.Key).Add(Receiver);
}

void MiniPubSub::FMessageMediator::Unregister(const int& Id, const FString& Key)
{
	TArray<FReceiver>* Receivers = ReceiverMap.Find(Key);
	if(Receivers != nullptr)
	{
		Receivers->RemoveAll([Id](const FReceiver& Receiver)
		{
			return Receiver.NodeId == Id;
		});
	}
}

// void MiniPubSub::FMessageMediator::Watch(const FReceiver& Receiver)
// {
// 	WatcherDic.Add(Receiver.NodeId, Receiver);
// }
//
// void FMessageMediator::Unwatch(const int& Id)
// {
// 	WatcherDic.Remove(Id);
// }

void MiniPubSub::FMessageMediator::Broadcast(const FRequest& Request)
{
	FReceiver InstantReceiver;
	if(InstantReceiverMap.RemoveAndCopyValue(Request.GetKey(), InstantReceiver))
	{
		InstantReceiver.ReceiveDelegate.ExecuteIfBound(Request);
		return;
	}
	
	if(TArray<FReceiver>* Receivers = ReceiverMap.Find(Request.Info.Key))
	{
		for (FReceiver Receiver : *Receivers)
		{
			if(Receiver.NodeId == Request.Info.NodeInfo.PublisherId)
				continue;
			Receiver.ReceiveDelegate.ExecuteIfBound(Request);
		}
	}

	static FString WatcherKey = TEXT("Key_Watcher_Reserved");
	if(TArray<FReceiver>* Watchers = ReceiverMap.Find(WatcherKey))
	{
		for(FReceiver Watcher : *Watchers)
		{
			if(Watcher.NodeId == Request.Info.NodeInfo.PublisherId)
			{
				continue;
			}
			Watcher.ReceiveDelegate.ExecuteIfBound(Request);
		}
	}
}

void MiniPubSub::FMessageMediator::RegisterInstant(FReceiver&& Receiver)
{
	InstantReceiverMap.Add(Receiver.Key, Receiver);
}
