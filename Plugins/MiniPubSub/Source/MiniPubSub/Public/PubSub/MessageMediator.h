#pragma once
#include "Receiver.h"

namespace MiniPubSub
{
	class MINIPUBSUB_API FMessageMediator
	{
		TMap<FString, TArray<FReceiver>> ReceiverMap = TMap<FString, TArray<FReceiver>>();
		TMap<FString, FReceiver> InstantReceiverMap = TMap<FString, FReceiver>();
		
	public:
		void Register(const FReceiver& Receiver);
		void Unregister(const int& Id, const FString& Key);
		void RegisterInstant(FReceiver&& Receiver);

		void Broadcast(const FMessage& Message);
	};	
}

