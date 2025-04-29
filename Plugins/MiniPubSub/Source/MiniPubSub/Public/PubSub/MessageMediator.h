#pragma once
#include "Handler.h"
#include "Receiver.h"

namespace MiniPubSub
{
	class MINIPUBSUB_API FMessageMediator
	{
		TMap<FString, TArray<FReceiver>> ReceiverMap = TMap<FString, TArray<FReceiver>>();
		TMap<FString, FReceiver> InstantReceiverMap = TMap<FString, FReceiver>();
		TMap<FString, FHandler> HandlerMap = TMap<FString, FHandler>();
		TMap<ESdkType, FHandler> TargetHandlerMap = TMap<ESdkType, FHandler>();
		
	public:
		void Register(const FReceiver& Receiver);
		void Unregister(const int& Id, const FString& Key);
		void RegisterInstant(FReceiver&& Receiver);
		void Broadcast(const FMessage& Message);
		void Handle(const FString& Key, FHandler&& Handler);
		void Handle(const ESdkType& Target, FHandler&& Handler);
		FPayload SendSync(const FMessage& Message);
	};	
}

