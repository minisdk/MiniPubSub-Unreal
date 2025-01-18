// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Module/ModuleBase.h"
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


class MINIPUBSUBUNREAL_API FNativeManager final : public FModuleBase
{
	FMessenger NativeMessenger;
	void OnSendToast(const FMessage& Message);

public:
	virtual ~FNativeManager() override = default;
	virtual void Initialize() override;
	
	void InitNativePubSub();
	void ShowToast(const FToastData& Toast);
};
