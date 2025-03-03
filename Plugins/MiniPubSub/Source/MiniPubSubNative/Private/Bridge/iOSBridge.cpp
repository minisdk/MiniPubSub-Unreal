// Fill out your copyright notice in the Description page of Project Settings.


#include "iOSBridge.h"
#if PLATFORM_IOS
using iOSNativeCallback = void (*)(const char* infoCStr, const char* dataCStr);
extern "C"
{
	void Initialize(iOSNativeCallback NativeCallback);
	void SendNative(const char* Info, const char* Json);
}
// #include "MiniPubSubNative/Thirdparty/iOS/MiniPubSub.framework/Headers/ObjcSide.h"
#endif
MiniPubSub::FIOSBridge* MiniPubSub::FIOSBridge::Instance = nullptr;

void NativeCallback(const char*  InfoText, const char* DataText)
{
	FString Info = UTF8_TO_TCHAR(InfoText);
	FString Data = UTF8_TO_TCHAR(DataText);
	bool _ = MiniPubSub::FIOSBridge::Instance->NativeHandle.ExecuteIfBound(Info, Data);
}

MiniPubSub::FIOSBridge::FIOSBridge()
{
#if PLATFORM_IOS
	Initialize(&NativeCallback);
	// [[ObjcSide sharedInstance] initializeWith:&NativeCallback];
#endif
	if(Instance == nullptr)
	{
		Instance = this;
	}
}

MiniPubSub::FIOSBridge::~FIOSBridge()
{
	if(Instance != nullptr)
		Instance = nullptr;
}

void MiniPubSub::FIOSBridge::Send(const FString& Info, const FString& Data)
{
#if PLATFORM_IOS
	SendNative(TCHAR_TO_UTF8(*Info), TCHAR_TO_UTF8(*Data));
	// [[ObjcSide sharedInstance] sendToNativeWithInfo:TCHAR_TO_UTF8(*Info) AndData: TCHAR_TO_UTF8(*Data)];
#endif
}

