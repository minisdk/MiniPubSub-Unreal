// Fill out your copyright notice in the Description page of Project Settings.

#include "MiniPubSubUnreal/Public/NativeManager.h"

#include "JsonObjectConverter.h"
#if PLATFORM_ANDROID
#include "Android/AndroidJavaEnv.h"
#elif PLATFORM_IOS
// #include "MiniPubSubUnreal/Thirdparty/iOS/sample.framework/Headers/sample-Swift.h"
extern "C"
{
	void Load();
}
#endif


void FNativeManager::OnSendToast(const MiniPubSub::FRequest& Request)
{
	TSharedPtr<FJsonObject> JsonObject = Request.ToJsonObject();
	if(JsonObject.IsValid())
	{
		FToastResult Result;
		if(FJsonObjectConverter::JsonObjectToUStruct<FToastResult>(JsonObject.ToSharedRef(), &Result))
		{
			UE_LOG(LogTemp, Display, TEXT("Toast Show Count : %d"), Result.ToastCount)
		}
	}
}

void FNativeManager::Initialize()
{
#if PLATFORM_ANDROID
	JNIEnv* JNIEnv = AndroidJavaEnv::GetJavaEnv();
	jclass AndroidBridgeClass = AndroidJavaEnv::FindJavaClass("com/pj/sample/SampleKitLoader");
	jmethodID InitializerMethodID = JNIEnv->GetStaticMethodID(AndroidBridgeClass, "load", "()V");
	JNIEnv->CallStaticVoidMethod(AndroidBridgeClass, InitializerMethodID, nullptr);
#elif PLATFORM_IOS
	Load();
#endif
}

void FNativeManager::InitNativePubSub()
{
	NativeMessenger.Subscribe(TEXT("SEND_TOAST_RESULT"), MiniPubSub::FReceiveDelegate::CreateRaw(this, &FNativeManager::OnSendToast));
}

void FNativeManager::ShowToast(const FToastData& Toast)
{
	// FJsonObjectConverter::UStructToJsonObject()

	TSharedPtr<FJsonObject> JsonObject = FJsonObjectConverter::UStructToJsonObject(Toast);
	if(JsonObject.IsValid())
	{
		MiniPubSub::FMessage Message = MiniPubSub::FMessage::FromJsonObject(JsonObject.ToSharedRef());
		NativeMessenger.Publish(TEXT("SEND_TOAST"), Message);
	}
}

void FNativeManager::ShowToastAsync(const FToastData& Toast)
{
	TSharedPtr<FJsonObject> JsonObject = FJsonObjectConverter::UStructToJsonObject(Toast);
	if(JsonObject.IsValid())
	{
		MiniPubSub::FMessage Message = MiniPubSub::FMessage::FromJsonObject(JsonObject.ToSharedRef());
		NativeMessenger.Publish(TEXT("SEND_TOAST_ASYNC"), Message, MiniPubSub::FReceiveDelegate::CreateLambda([](const MiniPubSub::FRequest& Request)
		{
			TSharedPtr<FJsonObject> ReceivedJsonObject = Request.ToJsonObject();
			if(!ReceivedJsonObject.IsValid())
			{
				return;
			}
			FToastResult Result;
			FJsonObjectConverter::JsonObjectToUStruct<FToastResult>(ReceivedJsonObject.ToSharedRef(), &Result);
			UE_LOG(LogTemp, Display, TEXT("Toast Show Async Count : %d"), Result.ToastCount)
		}));
	}
}
