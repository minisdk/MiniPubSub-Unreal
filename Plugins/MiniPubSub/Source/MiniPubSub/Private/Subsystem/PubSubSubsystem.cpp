// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/PubSubSubsystem.h"

void UPubSubSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogTemp, Display, TEXT("PubSubSubsystem init!"))
	
	if(!NativeRelay.IsValid())
	{
		NativeRelay = MakeUnique<FNativeRelay>();
	}
}

void UPubSubSubsystem::Deinitialize()
{
	Super::Deinitialize();
	UE_LOG(LogTemp, Display, TEXT("PubSubSubsystem deinit!"))
	if(NativeRelay.IsValid())
	{
		NativeRelay = nullptr;
	}
}
