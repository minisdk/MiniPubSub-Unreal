#pragma once
#include "MessageMediator.h"

namespace  MiniPubSub
{
	class MINIPUBSUB_API FMessageManager final
	{
	private:
		// TODO : cpp 만들어야함 : inline이될 수도 있음 -> 모듈 
		FMessageManager()
		: Mediator(FMessageMediator()){}
		FMessageManager(const FMessageManager& Other) = delete;
		FMessageManager& operator=(const FMessageManager& Other) = delete;
		FMessageManager(const FMessageManager&& Other) = delete;
		FMessageManager& operator=(const FMessageManager&& Other) = delete;
	
		FMessageMediator Mediator;
	
	public:
		static TSharedPtr<FMessageManager> Get();
		
		FMessageMediator& GetMediator();
	};	
}

