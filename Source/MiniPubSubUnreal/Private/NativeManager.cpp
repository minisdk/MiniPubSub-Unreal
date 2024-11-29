// Fill out your copyright notice in the Description page of Project Settings.

#include "MiniPubSubUnreal/Public/NativeManager.h"
#if PLATFORM_ANDROID
#include "Android/AndroidJavaEnv.h"
#elif PLATFORM_IOS
#include "MiniPubSubUnreal/Thirdparty/iOS/sample.framework/Headers/sample-Swift.h"
#endif

UNativeManager* UNativeManager::Instance = nullptr;

void UNativeManager::OnSendToast(const FMessage& Message)
{
	TMessage<FToastResult> Result = TMessage<FToastResult>(Message);
	UE_LOG(LogTemp, Display, TEXT("Toast Show Count : %d"), Result.Data().ToastCount)
}

void UNativeManager::InitializeModule()
{
#if PLATFORM_ANDROID
	JNIEnv* JNIEnv = AndroidJavaEnv::GetJavaEnv();
	jclass AndroidBridgeClass = AndroidJavaEnv::FindJavaClass("com/pj/sample/SampleKitLoader");
	jmethodID InitializerMethodID = JNIEnv->GetStaticMethodID(AndroidBridgeClass, "load", "()V");
	JNIEnv->CallStaticVoidMethod(AndroidBridgeClass, InitializerMethodID, nullptr);
#elif PLATFORM_IOS
	[SampleKitLoader loadModule];
#endif
	
}

UNativeManager::~UNativeManager()
{
	Instance = nullptr;
}

UNativeManager* UNativeManager::Get()
{
	if(Instance == nullptr)
	{
		Instance = NewObject<UNativeManager>();
	}
	return Instance;
}

void UNativeManager::InitNativePubSub()
{
	InitializeModule();
	NativeMessenger.Subscribe(TEXT("SEND_TOAST_RESULT"), FReceiveDelegate::CreateUObject(this, &UNativeManager::OnSendToast));
}

void UNativeManager::ShowToast(const FToastData& Toast)
{
	NativeMessenger.Publish(TMessage(TEXT("SEND_TOAST"), Toast));
}
