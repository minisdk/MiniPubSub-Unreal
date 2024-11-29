// Fill out your copyright notice in the Description page of Project Settings.


#include "iOSBridge.h"
#if PLATFORM_IOS
#include "MiniPubSub/Thirdparty/iOS/MiniPubSub.framework/Headers/ObjcSide.h"
#endif
FIOSBridge* FIOSBridge::Instance = nullptr;

void NativeCallback(const char*  InfoText, const char* DataText)
{
	FString Info = UTF8_TO_TCHAR(InfoText);
	FString Data = UTF8_TO_TCHAR(DataText);
	bool _ = FIOSBridge::Instance->NativeHandle.ExecuteIfBound(Info, Data);
}

FIOSBridge::FIOSBridge()
{
#if PLATFORM_IOS
	[[ObjcSide sharedInstance] initializeWith:&NativeCallback];
#endif
	if(Instance == nullptr)
	{
		Instance = this;
	}
}

FIOSBridge::~FIOSBridge()
{
	if(Instance != nullptr)
		Instance = nullptr;
}

void FIOSBridge::Send(const FString& Info, const FString& Data)
{
#if PLATFORM_IOS
	[[ObjcSide sharedInstance] sendToNativeWithInfo:TCHAR_TO_UTF8(*Info) AndData: TCHAR_TO_UTF8(*Data)];
#endif
}

