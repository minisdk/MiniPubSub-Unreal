// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeBridge.h"

/**
 * 
 */
class FMobileBridge : public INativeBridge
{
	TSharedPtr<INativeBridge> Bridge;

public:
	FMobileBridge();
	virtual ~FMobileBridge() override;

	static TSharedRef<FMobileBridge> Get();

	virtual void Send(const FString& Text) override;
};
