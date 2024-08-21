// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SampleBluprintLibrary.generated.h"


USTRUCT()
struct FTest
{
	GENERATED_BODY()

	UPROPERTY()
	FString str;
	UPROPERTY()
	int integer;
};

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

	UFUNCTION(BlueprintCallable, Category="PubSub Sample")
	static void JsonTest();

	UFUNCTION(BlueprintCallable, Category="PubSub Sample")
	static void MyTest();
};
