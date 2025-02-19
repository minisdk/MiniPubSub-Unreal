#pragma once
#include "PubSub/Messenger.h"

class FModuleBase
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

