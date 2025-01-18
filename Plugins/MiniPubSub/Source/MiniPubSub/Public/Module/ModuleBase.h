#pragma once
#include "PubSub/Messenger.h"

class MINIPUBSUB_API FModuleBase
{
	bool bInitialized = false;
	
public:
	virtual ~FModuleBase() = default;
	virtual void Initialize()
	{
		bInitialized = true;
	}
	
	bool IsInitialized() const
	{
		return bInitialized;
	}
};

