// Fill out your copyright notice in the Description page of Project Settings.


#include "iOSBridge.h"
#if PLATFORM_IOS
// #include "MiniPubSub/iOSBridge.h"
#include "MiniPubSub/Thirdparty/iOS/Bridge/iOSNativeBridge.h"
#endif
FIOSBridge* FIOSBridge::Instance = nullptr;

void NativeCallback(const char*  InfoText, const char* DataText)
{
	FString Info = UTF8_TO_TCHAR(InfoText);
	FString Data = UTF8_TO_TCHAR(DataText);
	UE_LOG(LogTemp, Display, TEXT("[Unreal] NativeCallback info : %s data : %s"), *Info, *Data)
	bool _ = FIOSBridge::Instance->NativeHandle.ExecuteIfBound(Info, Data);
}

FIOSBridge::FIOSBridge()
{
#if PLATFORM_IOS
	__iOSInitialize(&NativeCallback);
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
	UE_LOG(LogTemp, Display, TEXT("@@@@@ send to native : %s, data : %s"), *Info, *Data)
#if PLATFORM_IOS
	// const TCHAR* CInfo = *Info;
	// const TCHAR* CData = *Data;
	__iOSSend(TCHAR_TO_UTF8(*Info), TCHAR_TO_UTF8(*Data));
#endif
}

