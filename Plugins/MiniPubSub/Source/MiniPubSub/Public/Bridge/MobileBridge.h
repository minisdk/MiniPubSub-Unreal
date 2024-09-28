// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bridge/NativeBridge.h"

/**
 * 
 */
class FMobileBridge
{
	TSharedPtr<INativeBridge> Bridge;

public:
	FMobileBridge();

	// static TSharedRef<FMobileBridge> Get();

	void Send(const FString& Text);
	void BindNative(const FDelegate_Native_Text_Handler& Handle);
};
