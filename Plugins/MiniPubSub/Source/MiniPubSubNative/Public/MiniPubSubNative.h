#pragma once

#include "CoreMinimal.h"
#include "Bridge/NativeRelay.h"
#include "Modules/ModuleManager.h"

class FMiniPubSubNativeModule : public IModuleInterface
{
private:
    MiniPubSub::FNativeRelay NativeRelay;
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
