// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bridge/NativeBridge.h"
#if PLATFORM_ANDROID
#include "Android/AndroidJavaEnv.h"
#endif
/**
 * 
 */

class FAndroidBridge : public INativeBridge
{
#if PLATFORM_ANDROID
	TSharedPtr<JNIEnv> JNIEnv;
	jobject AndroidBridgeObject;
	jmethodID SendTextMethod;
#endif

public:
	FAndroidBridge();
	virtual ~FAndroidBridge() override;

	virtual void Send(const FString& Info, const FString& Data) override;
};
