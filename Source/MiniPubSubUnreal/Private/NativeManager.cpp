// Fill out your copyright notice in the Description page of Project Settings.

#include "MiniPubSubUnreal/Public/NativeManager.h"

UNativeManager* UNativeManager::Instance = nullptr;

void UNativeManager::OnSendToast(TSharedPtr<const FMessage> Message)
{
	TSharedPtr<const TMessage<FToastResult>> Result = TMessage<FToastResult>::Convert(Message);
	UE_LOG(LogTemp, Display, TEXT("Toast Show Count : %d"), Result->Data().ToastShowCount)
}

UNativeManager::~UNativeManager()
{
	Instance = nullptr;
}

UNativeManager* UNativeManager::Get()
{
	if(Instance == nullptr)
	{
		Instance = NewObject<UNativeManager>();
	}
	return Instance;
}

void UNativeManager::InitNativePubSub()
{
	NativeMessenger.Subscribe(TEXT("SEND_TOAST_RESULT"), FReceiveDelegate::CreateUObject(this, &UNativeManager::OnSendToast));
}

void UNativeManager::ShowToast(const FToastData& Toast)
{
	NativeMessenger.Publish(TMessage<FToastData>::Create(TEXT("SEND_TOAST"), Toast));
}
