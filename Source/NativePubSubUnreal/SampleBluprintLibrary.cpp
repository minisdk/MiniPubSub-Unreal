// Fill out your copyright notice in the Description page of Project Settings.


#include "SampleBluprintLibrary.h"

#include "MyTester.h"

void USampleBluprintLibrary::CallNativeTest(const FString& Text)
{
	UE_LOG(LogTemp, Warning, TEXT("Native Test Called! %s"), *Text);
	FMyTester::CallTest(Text);
	}

void USampleBluprintLibrary::CallBytesTest(const TArray<uint8>& Bytes)
{
	UE_LOG(LogTemp, Warning, TEXT("Byte Test Called! %s"), Bytes.GetData());
	auto b = Bytes.GetData();
	const TArray<char> CharArray(Bytes);
	FMyTester::CallByteTest(CharArray);
}