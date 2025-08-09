// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bridge/NativeBridge.h"

namespace MiniPubSub
{
	/**
	 * 
	 */
	class FIOSBridge final : public INativeBridge
	{
	private:
	public:
		static FIOSBridge* Instance;
		
		FIOSBridge();
		virtual ~FIOSBridge() override;
		
		virtual void Send(const FString& Info, const FString& Data) override;
		virtual FString SendSync(const FString& Info, const FString& Data) override;
	};
}
