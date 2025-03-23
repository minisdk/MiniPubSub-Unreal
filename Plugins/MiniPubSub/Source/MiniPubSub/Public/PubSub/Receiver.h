// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Data/Message.h"

namespace MiniPubSub
{
	DECLARE_DELEGATE_OneParam(FReceiveDelegate, const FMessage& /*Message*/);

	struct MINIPUBSUB_API FReceiver final
	{
		int NodeId;
		FString Key;
		ESdkType Target;
		FReceiveDelegate ReceiveDelegate;

		FReceiver()
		: NodeId(-1)
		, Target(ESdkType::Game)
		{
		}

		FReceiver(const int& Id, const FString& InKey, const ESdkType& InTarget, const FReceiveDelegate& Delegate)
		: NodeId(Id)
		, Key(InKey)
		, Target(InTarget)
		, ReceiveDelegate(Delegate){}

		bool CanInvoke(FMessageInfo Info) const
		{
			return NodeId != Info.NodeInfo.PublisherId && Target == Info.Topic.GetTarget();
		}
	};

}

