// Fill out your copyright notice in the Description page of Project Settings.


#include "AndroidBridge.h"

FDelegate_Native_Text_Handler DelNativeTextCallback;
FDelegate_Native_Data_Handler DelNativeDataCallback;

FAndroidBridge::FAndroidBridge()
{
#if PLATFORM_ANDROID
	JNIEnv = MakeShareable(AndroidJavaEnv::GetJavaEnv());
	UE_LOG(LogTemp, Display, TEXT("Find java class : com/pj/pubsub/unreal/NativeBridge"))
	jclass AndroidBridgeClass = AndroidJavaEnv::FindJavaClass("com/pj/pubsub/unreal/NativeBridge");
	jmethodID ConstructorID = JNIEnv->GetMethodID(AndroidBridgeClass, "<init>", "()V");
	AndroidBridgeObject = JNIEnv->NewObject(AndroidBridgeClass, ConstructorID);
	SendTextMethod = JNIEnv->GetMethodID(AndroidBridgeClass, "send", "(Ljava/lang/String;)V");
	SendDataMethod = JNIEnv->GetMethodID(AndroidBridgeClass, "send", "([B)V");

	JNIEnv->DeleteLocalRef(AndroidBridgeClass);
#endif
	DelNativeTextCallback.BindLambda([this](const FString& Text)
	{
		this->DelNativeTextHandle.Execute(Text);
	});
	DelNativeDataCallback.BindLambda([this](const TArray<byte>& Data)
	{
		this->DelNativeDataHandle.Execute(Data);
	});
}

FAndroidBridge::~FAndroidBridge()
{
}

void FAndroidBridge::Send(const FString& Text)
{
#if PLATFORM_ANDROID
	std::string StdText(TCHAR_TO_UTF8(*Text));
	jstring JavaText = JNIEnv->NewStringUTF(StdText.c_str());
	JNIEnv->CallVoidMethod(AndroidBridgeObject, SendTextMethod, JavaText);
	JNIEnv->DeleteLocalRef(JavaText);
#endif
}

#if PLATFORM_ANDROID
JNI_METHOD void Java_com_pj_pubsub_unreal_NativeBridge_nativeCallback(JNIEnv* jenv, jobject Obj, jstring Text)
{
	FString UnrealText = FJavaHelper::FStringFromLocalRef(jenv, Text);
	DelNativeTextCallback.Execute(UnrealText);
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
