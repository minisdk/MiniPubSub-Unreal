// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Data/Message.h"

namespace MiniPubSub
{
	DECLARE_DELEGATE_OneParam(FReceiveDelegate, const FMessage& /*Request*/);

	struct MINIPUBSUB_API FReceiver final
	{
		int NodeId;
		FString Key;
		FReceiveDelegate ReceiveDelegate;

		FReceiver(): NodeId(-1)
		{
		}

		FReceiver(const int& Id, const FString& Key, const FReceiveDelegate& Delegate)
		: NodeId(Id)
		, Key(Key)
		, ReceiveDelegate(Delegate){}
	};

}

