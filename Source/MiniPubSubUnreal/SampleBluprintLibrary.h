// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Public/NativeManager.h"
#include "SampleBluprintLibrary.generated.h"


/**
 * 
 */
UCLASS()
class MINIPUBSUBUNREAL_API USampleBluprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	

	UFUNCTION(BlueprintCallable, Category="PubSub Sample")
	static void PubSubInitTest();

	UFUNCTION(BlueprintCallable, Category="PubSub Sample")
	static void SendNativeTest(const FToastData& Data);
};
