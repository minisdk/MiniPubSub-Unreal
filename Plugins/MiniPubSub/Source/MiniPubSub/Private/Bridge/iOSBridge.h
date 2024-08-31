// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeBridge.h"

/**
 * 
 */
class FIOSBridge : public INativeBridge
{
public:
	FIOSBridge();
	virtual ~FIOSBridge() override;
	
	virtual void Send(const FString& Text) override;
};
