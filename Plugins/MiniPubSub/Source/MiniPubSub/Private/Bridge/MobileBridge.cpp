// Fill out your copyright notice in the Description page of Project Settings.

#include "Bridge/MobileBridge.h"

#if PLATFORM_ANDROID
#include "AndroidBridge.h"
#elif PLATFORM_IOS
#include "iOSBridge.h"
#endif


FMobileBridge::FMobileBridge()
{
#if PLATFORM_ANDROID
	this->Bridge = MakeShareable(new FAndroidBridge());
#elif PLATFORM_IOS
	this->Bridge = MakeShareable(new FIOSBridge());
#else
#endif
	// this->Bridge->DelNativeTextHandle.BindLambda([this](const FString& Text)
	// {
	// 	this->DelNativeTextHandle.Execute(Text);
	// });
}

// TSharedRef<FMobileBridge> FMobileBridge::Get()
// {
// 	static TSharedRef<FMobileBridge> MobileBridge = MakeShareable(new FMobileBridge());
// 	return MobileBridge;
// }

void FMobileBridge::Send(const FString& Text)
{
	this->Bridge.Get()->Send(Text);
}

void FMobileBridge::BindNative(const FDelegate_Native_Text_Handler& Handle)
{
	this->Bridge->DelNativeTextHandle = Handle;
}
