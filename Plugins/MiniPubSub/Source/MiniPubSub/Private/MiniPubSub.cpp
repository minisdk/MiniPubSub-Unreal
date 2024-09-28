// Copyright Epic Games, Inc. All Rights Reserved.

#include "MiniPubSub.h"

#define LOCTEXT_NAMESPACE "FMiniPubSubModule"

void FMiniPubSubModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	if(GIsEditor)
		return;
#if PLATFORM_ANDROID || PLATFORM_IOS
	this->NativeRelay = new FNativeRelay();
#endif
}

void FMiniPubSubModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	if(GIsEditor)
    		return;
    #if PLATFORM_ANDROID || PLATFORM_IOS
    	delete this->NativeRelay;
    #endif
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMiniPubSubModule, MiniPubSub)