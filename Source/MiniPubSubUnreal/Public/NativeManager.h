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

UCLASS()
class MINIPUBSUBUNREAL_API UNativeManager : public UObject
{
	GENERATED_BODY()
	FMessenger NativeMessenger;
	void OnSendToast(const FMessage& Message);

	static UNativeManager* Instance;

	void InitializeModule();
public:
	~UNativeManager();
	
	static UNativeManager* Get();
	void InitNativePubSub();
	void ShowToast(const FToastData& Toast);
};
