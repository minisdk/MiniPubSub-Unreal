// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Data/Message.h"

DECLARE_DELEGATE_OneParam(FReceiveDelegate, TSharedPtr<const FMessage> /*Message*/);

struct MINIPUBSUB_API FReceiver final
{
	const int NodeId;
	const FString Key;
	const FReceiveDelegate ReceiveDelegate;

	FReceiver(const int& Id, const FString& Key, const FReceiveDelegate& Delegate)
	: NodeId(Id)
	, Key(Key)
	, ReceiveDelegate(Delegate){}
};
