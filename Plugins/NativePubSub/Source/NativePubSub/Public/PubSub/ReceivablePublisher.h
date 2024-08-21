// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Message.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FReceiveDelegate, const FMessage& /*Message*/);

// public class FReceiver

class NATIVEPUBSUB_API INode
{
public:
	virtual ~INode(){};
	virtual int Id() = 0;
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

// class NATIVEPUBSUB_API IReceivable
// {
// public:
// 	IReceivable(){}
// 	virtual ~IReceivable(){};
//
// 	virtual void SetReceivingRule(const FTag& Tag) = 0;
// 	virtual bool MatchTag(const FTag& Tag) = 0;
// 	
// };

// class NATIVEPUBSUB_API Publisher
// {
// public:
// 	Publisher();
// 	virtual ~Publisher();
//
// 		
// 	
// };


// class NATIVEPUBSUB_API FReceivablePublisher : public IReceivable
// {
// public:
// 	FReceivablePublisher();
// 	virtual ~FReceivablePublisher() override;
//
// 	
// };
