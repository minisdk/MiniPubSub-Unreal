#pragma once
#include "MessageMediator.h"

class MINIPUBSUB_API FMessageManager final
{
private:
	// static TSharedPtr<FMessageManager> Instance;

	FMessageManager()
	: Mediator(FMessageMediator()){}
	FMessageManager(const FMessageManager& Other) = delete;
	FMessageManager& operator=(const FMessageManager& Other) = delete;
	FMessageManager(const FMessageManager&& Other) = delete;
	FMessage& operator=(const FMessageManager&& Other) = delete;
	
	FMessageMediator Mediator;
	
public:
	static TSharedPtr<FMessageManager> Get()
	{
		static TSharedPtr<FMessageManager> Instance;
		if(Instance == nullptr || !Instance.IsValid())
		{
			Instance = MakeShareable(new FMessageManager());
		}
		return Instance;
	}

	FMessageMediator& GetMediator() 
	{
		return Mediator;
	}
};
