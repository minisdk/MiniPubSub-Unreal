#include "PubSub/MessageMediator.h"

void MiniPubSub::FMessageMediator::Register(const FReceiver& Receiver)
{
	TArray<FReceiver>& Receivers = ReceiverMap.FindOrAdd(Receiver.Key);
	int32 Index = Receivers.IndexOfByPredicate([Id = Receiver.NodeId](const FReceiver& Element)
	{
		return Element.NodeId == Id;
	});
	if(Index != INDEX_NONE)
	{
		Receivers.RemoveAtSwap(Index);
	}
	Receivers.Add(Receiver);
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

void MiniPubSub::FMessageMediator::RegisterInstant(FReceiver&& Receiver)
{
	InstantReceiverMap.Add(Receiver.Key, Receiver);
}

void MiniPubSub::FMessageMediator::Broadcast(const FMessage& Message)
{
	FReceiver InstantReceiver;
	if(InstantReceiverMap.RemoveAndCopyValue(Message.GetKey(), InstantReceiver))
	{
		InstantReceiver.ReceiveDelegate.ExecuteIfBound(Message);
		return;
	}
	
	if(TArray<FReceiver>* Receivers = ReceiverMap.Find(Message.Info.Topic.Key))
	{
		for (FReceiver Receiver : *Receivers)
		{
			if(Receiver.CanInvoke(Message.Info))
			{
				Receiver.ReceiveDelegate.ExecuteIfBound(Message);
			}
		}
	}

	static FString WatcherKey = TEXT("Key_Watcher_Reserved");
	if(TArray<FReceiver>* Watchers = ReceiverMap.Find(WatcherKey))
	{
		for(FReceiver Watcher : *Watchers)
		{
			if(Watcher.CanInvoke(Message.Info))
			{
				Watcher.ReceiveDelegate.ExecuteIfBound(Message);
			}
		}
	}
}

void MiniPubSub::FMessageMediator::Handle(const FString& Key, FHandler&& Handler)
{
	HandlerMap.Add(Key, Handler);
}

void MiniPubSub::FMessageMediator::Handle(const ESdkType& Target, FHandler&& Handler)
{
	TargetHandlerMap.Add(Target, Handler);
}

MiniPubSub::FPayload MiniPubSub::FMessageMediator::SendSync(const FMessage& Message)
{
	if(FHandler* Handler = HandlerMap.Find(Message.GetKey()))
	{
		if(Handler->CanInvoke(Message.Info))
		{
			return Handler->HandleDelegate.Execute(Message);
		}
	}

	const ESdkType Target =  Message.Info.Topic.GetTarget();
	if(FHandler* TargetHandler = TargetHandlerMap.Find(Target))
	{
		if(TargetHandler->CanInvoke(Message.Info))
		{
			return TargetHandler->HandleDelegate.Execute(Message);
		}
	}
	return FPayload("{}");
}
