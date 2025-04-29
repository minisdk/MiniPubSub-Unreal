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


void FNativeManager::OnSendToast(const MiniPubSub::FMessage& Message)
{
	TSharedPtr<FJsonObject> JsonObject = Message.ToJsonObject();
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
		MiniPubSub::FPayload Message = MiniPubSub::FPayload::FromJsonObject(JsonObject.ToSharedRef());
		NativeMessenger.Publish(MiniPubSub::FTopic(TEXT("SEND_TOAST"), MiniPubSub::ESdkType::Native), Message);
	}
}

void FNativeManager::ShowToastAsync(const FToastData& Toast)
{
	TSharedPtr<FJsonObject> JsonObject = FJsonObjectConverter::UStructToJsonObject(Toast);
	if(JsonObject.IsValid())
	{
		MiniPubSub::FPayload Message = MiniPubSub::FPayload::FromJsonObject(JsonObject.ToSharedRef());
		NativeMessenger.Publish(MiniPubSub::FTopic(TEXT("SEND_TOAST_ASYNC"), MiniPubSub::ESdkType::Native), Message
			, MiniPubSub::FReceiveDelegate::CreateLambda([](const MiniPubSub::FMessage& Message)
		{
			TSharedPtr<FJsonObject> ReceivedJsonObject = Message.ToJsonObject();
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

void FNativeManager::ShowToastSync(const FToastData& Toast)
{
	TSharedPtr<FJsonObject> JsonObject = FJsonObjectConverter::UStructToJsonObject(Toast);
	if(JsonObject.IsValid())
	{
		MiniPubSub::FPayload Message = MiniPubSub::FPayload::FromJsonObject(JsonObject.ToSharedRef());
		MiniPubSub::FPayload ResultPayload = NativeMessenger.SendSync(MiniPubSub::FTopic(TEXT("SEND_TOAST_SYNC"), ::MiniPubSub::ESdkType::Native), Message);

		TSharedPtr<FJsonObject> ReceivedJsonObject = ResultPayload.ToJsonObject();
		if(!ReceivedJsonObject.IsValid())
		{
			return;
		}
		FToastResult Result;
		FJsonObjectConverter::JsonObjectToUStruct<FToastResult>(ReceivedJsonObject.ToSharedRef(), &Result);
		UE_LOG(LogTemp, Display, TEXT("Toast Show Async Count : %d"), Result.ToastCount)
	}
}
