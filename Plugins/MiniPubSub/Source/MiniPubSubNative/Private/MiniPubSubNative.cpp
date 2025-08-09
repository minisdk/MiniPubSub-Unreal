#include "MiniPubSubNative.h"

#include "Bridge/NativeRelay.h"

#define LOCTEXT_NAMESPACE "FMiniPubSubNativeModule"

void FMiniPubSubNativeModule::StartupModule()
{
    NativeRelay.Initialize();
}

void FMiniPubSubNativeModule::ShutdownModule()
{
    
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FMiniPubSubNativeModule, MiniPubSubNative)