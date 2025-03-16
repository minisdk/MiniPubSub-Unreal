// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PubSub/Messenger.h"
#include "UObject/Object.h"
#include "NativeManager.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FToastData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ToastMessage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int ToastDuration;
};

USTRUCT()
struct FToastResult
{
	GENERATED_BODY()

	UPROPERTY()
	int ToastCount;
};


class MINIPUBSUBUNREAL_API FNativeManager final
{
	MiniPubSub::FMessenger NativeMessenger;
	void OnSendToast(const MiniPubSub::FMessage& Message);

public:
	void Initialize();
	
	void InitNativePubSub();
	void ShowToast(const FToastData& Toast);
	void ShowToastAsync(const FToastData& Toast);
};
