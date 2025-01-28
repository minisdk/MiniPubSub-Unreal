// Fill out your copyright notice in the Description page of Project Settings.


#include "AndroidBridge.h"

FDelegate_Native_Handler DelNativeAndroidCallback;

FAndroidBridge::FAndroidBridge()
{
#if PLATFORM_ANDROID
	JNIEnv = AndroidJavaEnv::GetJavaEnv();
	jclass AndroidBridgeClass = AndroidJavaEnv::FindJavaClass("com/minisdk/pubsub/bridge/UnrealNativeBridge");
	jmethodID ConstructorID = JNIEnv->GetMethodID(AndroidBridgeClass, "<init>", "()V");
	AndroidBridgeObject = JNIEnv->NewObject(AndroidBridgeClass, ConstructorID);
	SendMessageMethod = JNIEnv->GetMethodID(AndroidBridgeClass, "send", "(Ljava/lang/String;Ljava/lang/String;)V");
	JNIEnv->DeleteLocalRef(AndroidBridgeClass);
#endif
	DelNativeAndroidCallback.BindLambda([this](const FString& Info, const FString& Data)
	{
		bool _ = this->NativeHandle.ExecuteIfBound(Info, Data);
	});
}

FAndroidBridge::~FAndroidBridge()
{
#if PLATFORM_ANDROID
	JNIEnv->DeleteLocalRef(AndroidBridgeObject);
#endif
}

void FAndroidBridge::Send(const FString& Info, const FString& Data)
{
#if PLATFORM_ANDROID
	std::string StdInfo(TCHAR_TO_UTF8(*Info));
	jstring JavaInfo = JNIEnv->NewStringUTF(TCHAR_TO_UTF8(*Info));

	std::string StdData(TCHAR_TO_UTF8(*Data));
	jstring JavaData = JNIEnv->NewStringUTF(TCHAR_TO_UTF8(*Data));
	
	JNIEnv->CallVoidMethod(AndroidBridgeObject, SendMessageMethod, JavaInfo, JavaData);
	JNIEnv->DeleteLocalRef(JavaInfo);
	JNIEnv->DeleteLocalRef(JavaData);
#endif
}

#if PLATFORM_ANDROID
JNI_METHOD void Java_com_minisdk_pubsub_bridge_UnrealNativeBridge_nativeCallback(JNIEnv* jenv, jobject Obj, jstring Info, jstring Data)
{
	FString UnrealInfo = FJavaHelper::FStringFromLocalRef(jenv, Info);
	FString UnrealData = FJavaHelper::FStringFromLocalRef(jenv, Data);
	DelNativeAndroidCallback.Execute(UnrealInfo, UnrealData);
}
#endif
