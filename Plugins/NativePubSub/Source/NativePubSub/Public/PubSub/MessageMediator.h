#pragma once
#include "ReceivablePublisher.h"

class FMessageMediator
{
private:
	TMap<FString, TArray<FReceiver>> ReceiverDic = TMap<FString, TArray<FReceiver>>();
	TMap<int, FReceiver> WatcherDic = TMap<int, FReceiver>();
public:
	void Register(const FReceiver& Receiver);
	void Unregister(const int& Id, const FString& Key);

	void Watch(const FReceiver& Receiver);
	void Unwatch(const int& Id);

	void Publish(TSharedPtr<const FMessage> Message, const int& PublisherId);
};
