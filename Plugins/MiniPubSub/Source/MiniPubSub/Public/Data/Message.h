// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JsonObjectConverter.h"
#include "Message.generated.h"

USTRUCT()
struct MINIPUBSUB_API FMessageInfo
{
	GENERATED_BODY()

	UPROPERTY()
	FString Key;

	FMessageInfo(){}
	
	FMessageInfo(const FString& Key)
	: Key(Key)
	{}
};

/**
 * FMessage is base message class
 */
struct MINIPUBSUB_API FMessage
{
	const FMessageInfo Info;
	FString Json;
	
	FMessage(const FMessageInfo& Info, const FString& Data)
	: Info(Info)
	, Json(Data)
	{}
	virtual ~FMessage(){};
	
protected:
	explicit FMessage(const FString& Key)
	: Info(FMessageInfo(Key))
	{}
};

/**
 * TMessage contains serialized UStruct data.
 */
template<typename DataType>
struct MINIPUBSUB_API TMessage final :  FMessage
{
	TMessage(const FString& Key, const DataType& Data)
	: FMessage(Key)
	{
		FJsonObjectConverter::UStructToJsonObjectString<DataType>(Data, this->Json);
	}

	explicit TMessage(const FMessage& Message)
	:FMessage(Message)
	{}
	
	virtual ~TMessage() override
	{
		
	}
	
	DataType Data() const
	{
		DataType Data;
		FJsonObjectConverter::JsonObjectStringToUStruct(this->Json, &Data);
		return Data;
	}
};
