// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Message.h"

DECLARE_DELEGATE_OneParam(FReceiveDelegate, TSharedPtr<const FMessage> /*Message*/);

// public class FReceiver

class NATIVEPUBSUB_API INode
{
public:
	virtual ~INode(){};
	virtual const int Id() const = 0;
};

class NATIVEPUBSUB_API ISubscribable : public INode
{
public:
	virtual void Subscribe(const FString& Key, const FReceiveDelegate& ReceiveDelegate) = 0;
	virtual void Unsubscribe(const FString& Key) = 0;
};

class NATIVEPUBSUB_API IWatchable : public INode
{
public:
	virtual void Watch(const FReceiveDelegate& ReceiveDelegate) = 0;
	virtual void Unwatch() = 0;
};

struct FReceiver final
{
	const int NodeId;
	const FString Key;
	const FReceiveDelegate ReceiveDelegate;

	FReceiver(const int& Id, const FString& Key, const FReceiveDelegate& Delegate)
	: NodeId(Id)
	, Key(Key)
	, ReceiveDelegate(Delegate){}
};
