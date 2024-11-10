// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bridge/NativeRelay.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PubSubSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class MINIPUBSUB_API UPubSubSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
private:
	TUniquePtr<FNativeRelay> NativeRelay; 
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
};
