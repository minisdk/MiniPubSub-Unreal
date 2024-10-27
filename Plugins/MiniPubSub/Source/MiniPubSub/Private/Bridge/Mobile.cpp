// Fill out your copyright notice in the Description page of Project Settings.

#include "Bridge/Mobile.h"

#if PLATFORM_ANDROID
#include "AndroidBridge.h"
#elif PLATFORM_IOS
#include "iOSBridge.h"
#endif


FMobile::FMobile()
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

void FMobile::Send(const FString& Info, const FString& Data)
{
	this->Bridge.Get()->Send(Info, Data);
}

void FMobile::BindNative(const FDelegate_Native_Handler& Handle)
{
	this->Bridge->NativeHandle = Handle;
}
