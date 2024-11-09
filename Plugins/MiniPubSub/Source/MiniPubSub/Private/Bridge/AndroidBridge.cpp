// Fill out your copyright notice in the Description page of Project Settings.


#include "AndroidBridge.h"

FDelegate_Native_Handler DelNativeAndroidCallback;

FAndroidBridge::FAndroidBridge()
{
#if PLATFORM_ANDROID
	JNIEnv = AndroidJavaEnv::GetJavaEnv();
	UE_LOG(LogTemp, Display, TEXT("Find java class : com/minisdk/pubsub/unreal/NativeBridge"))
	jclass AndroidBridgeClass = AndroidJavaEnv::FindJavaClass("com/minisdk/pubsub/unreal/NativeBridge");
	jmethodID ConstructorID = JNIEnv->GetMethodID(AndroidBridgeClass, "<init>", "()V");
	AndroidBridgeObject = JNIEnv->NewObject(AndroidBridgeClass, ConstructorID);
	SendMessageMethod = JNIEnv->GetMethodID(AndroidBridgeClass, "send", "(Ljava/lang/String;Ljava/lang/String;)V");
	UE_LOG(LogTemp, Display, TEXT("delete AndroidBridgeClass"))
	JNIEnv->DeleteLocalRef(AndroidBridgeClass);
	UE_LOG(LogTemp, Display, TEXT("delete AndroidBridgeClass ok"))
#endif
	DelNativeAndroidCallback.BindLambda([this](const FString& Info, const FString& Data)
	{
		bool _ = this->NativeHandle.ExecuteIfBound(Info, Data);
	});
	// DelNativeDataCallback.BindLambda([this](const TArray<byte>& Data)
	// {
	// 	this->DelNativeDataHandle.Execute(Data);
	// });
}

FAndroidBridge::~FAndroidBridge()
{
#if PLATFORM_ANDROID
	// JNIEnv->DeleteLocalRef(SendMessageMethod);
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
JNI_METHOD void Java_com_minisdk_pubsub_unreal_NativeBridge_nativeCallback(JNIEnv* jenv, jobject Obj, jstring Info, jstring Data)
{
	FString UnrealInfo = FJavaHelper::FStringFromLocalRef(jenv, Info);
	FString UnrealData = FJavaHelper::FStringFromLocalRef(jenv, Data);
	DelNativeAndroidCallback.Execute(UnrealInfo, UnrealData);
}
// JNI_METHOD void Java_com_pj_pubsub_unreal_NativeBridge_nativeDataCallback(JNIEnv* jenv, jobject Obj, jbyteArray jDataArray)
// {
// 	jbyte* jData = jenv->GetByteArrayElements(jDataArray, NULL);
// 	jsize Length = jenv->GetArrayLength(jDataArray);
//
// 	TArray<byte> Data((size_t)Length);
// 	for(jsize i = 0; i < Length; i++)
// 	{
// 		Data[i] = jData[i];
// 	}
// 	DelNativeDataCallback.Excute(Data);
// }
#endif
