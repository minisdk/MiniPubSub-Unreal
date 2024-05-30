// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SampleBluprintLibrary.generated.h"

/**
 * 
 */
UCLASS()
class NATIVEPUBSUBUNREAL_API USampleBluprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category="PubSub Sample")
	static void CallNativeTest(const FString& Text);

	UFUNCTION(BlueprintCallable, Category="PubSub Sample")
	static void CallBytesTest(const TArray<uint8> &Bytes);
};
