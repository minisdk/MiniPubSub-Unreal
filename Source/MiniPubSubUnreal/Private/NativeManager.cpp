// Fill out your copyright notice in the Description page of Project Settings.

#include "MiniPubSubUnreal/Public/NativeManager.h"
#if PLATFORM_ANDROID
#include "Android/AndroidJavaEnv.h"
#elif PLATFORM_IOS
#include "MiniPubSubUnreal/Thirdparty/iOS/sample.framework/Headers/sample-Swift.h"
#endif

void FNativeManager::OnSendToast(const FMessage& Message)
{
	TMessage<FToastResult> Result = TMessage<FToastResult>(Message);
	UE_LOG(LogTemp, Display, TEXT("Toast Show Count : %d"), Result.Data().ToastCount)
}

void FNativeManager::Initialize()
{
	FModuleBase::Initialize();
#if PLATFORM_ANDROID
	JNIEnv* JNIEnv = AndroidJavaEnv::GetJavaEnv();
	jclass AndroidBridgeClass = AndroidJavaEnv::FindJavaClass("com/pj/sample/SampleKitLoader");
	jmethodID InitializerMethodID = JNIEnv->GetStaticMethodID(AndroidBridgeClass, "load", "()V");
	JNIEnv->CallStaticVoidMethod(AndroidBridgeClass, InitializerMethodID, nullptr);
#elif PLATFORM_IOS
	[SampleKitLoader loadModule];
#endif
}

void FNativeManager::InitNativePubSub()
{
	NativeMessenger.Subscribe(TEXT("SEND_TOAST_RESULT"), FReceiveDelegate::CreateRaw(this, &FNativeManager::OnSendToast));
}

void FNativeManager::ShowToast(const FToastData& Toast)
{
	NativeMessenger.Publish(TMessage(TEXT("SEND_TOAST"), Toast));
}
