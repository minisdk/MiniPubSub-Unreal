// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bridge/NativeBridge.h"


namespace MiniPubSub
{
	
	/**
	 * 
	 */
	class FMobile
	{
		TSharedPtr<INativeBridge> Bridge;

	public:
		FMobile();

		// static TSharedRef<FMobileBridge> Get();

		void Send(const FString& Info, const FString& Data);
		FString SendSync(const FString& Info, const FString& Data);
		void BindNative(const FDelegate_Native_Handler& Handle);
	};
}
