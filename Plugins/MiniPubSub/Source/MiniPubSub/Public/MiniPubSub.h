// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Bridge/NativeRelay.h"
#include "Modules/ModuleManager.h"

class FMiniPubSubModule : public IModuleInterface
{
private:
	FNativeRelay* NativeRelay;
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
