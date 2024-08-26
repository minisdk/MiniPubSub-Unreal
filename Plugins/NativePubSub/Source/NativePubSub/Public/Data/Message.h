// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JsonObjectConverter.h"

/**
 * 
 */

struct NATIVEPUBSUB_API FMessage
{
public:
	enum class EMessageType
	{
		Base,
		UStruct,
	};

	const EMessageType MessageType;  
	const FString Key;
	
protected:
	const TSharedPtr<FJsonValue> DataJson;
	const EJson DataJsonType;

private:
	FMessage(const FString& Key)
	: MessageType(EMessageType::Base)
	, Key(Key)
	, DataJson(nullptr)
	, DataJsonType(EJson::Null)
	{}

	FMessage(const FString& Key, const TSharedPtr<FJsonValue>& DataJson)
	: MessageType(EMessageType::Base)
	, Key(Key)
	, DataJson(DataJson)
	, DataJsonType(DataJson->Type)
	{}
	
protected:
	FMessage(const FString& Key, const EMessageType& MessageType)
	: MessageType(MessageType)
	, Key(Key)
	, DataJson(nullptr)
	, DataJsonType(EJson::Null)
	{}

public:
	virtual ~FMessage(){};
	virtual FString ToString() const{return Key;}

	static TSharedPtr<const FMessage> Create(const FString& Key)
	{
		return MakeShareable(new FMessage(Key));
	}

	static TSharedPtr<const FMessage> ParseFrom(const FString& Json)
	{
		const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Json);
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
		FJsonSerializer::Deserialize(Reader, JsonObject);

		TSharedPtr<FMessage> MessageParsed = MakeShareable(new FMessage(JsonObject->GetStringField(TEXT("Key")), JsonObject->TryGetField(TEXT("Data"))));
		return MessageParsed;
	}
};

template<typename DataType>
struct NATIVEPUBSUB_API TMessage final :  FMessage
{
private:
	DataType *DataPtr;

	TMessage(const FString& Key, const DataType& Data)
	: FMessage(Key, EMessageType::UStruct)
	, DataPtr(new DataType(Data))
	{}

	explicit TMessage(const FMessage& Message)
	:FMessage(Message)
	{
		if(DataJsonType == EJson::Object)
		{
			DataPtr = new DataType();
			FJsonObjectConverter::JsonObjectToUStruct(DataJson->AsObject().ToSharedRef(), DataPtr);
		}
	}
	
public:
	virtual ~TMessage() override
	{
		delete DataPtr;
	}

	const DataType& Data() const
	{
		return *DataPtr;
	}
	
	virtual FString ToString() const override
	{
		const TSharedRef<FJsonObject> JsonObjectRef = MakeShareable(new FJsonObject());
		JsonObjectRef->SetStringField(TEXT("Key"), Key);
		
		TSharedPtr<FJsonObject> DataObject = FJsonObjectConverter::UStructToJsonObject(*DataPtr);
		if(DataObject.IsValid())
		{
			JsonObjectRef->SetObjectField(TEXT("Data"), DataObject);
		}
		
		FString JsonString;
		const TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&JsonString);
		FJsonSerializer::Serialize(JsonObjectRef, JsonWriter);
		return JsonString;
	}

	static TSharedPtr<const TMessage> Create(const FString& Key, const DataType& Data)
	{
		return MakeShareable(new TMessage(Key, Data));
	}
	
	static TSharedPtr<const TMessage> Convert(const TSharedPtr<const FMessage>& MessagePtr)
	{
		check(MessagePtr.IsValid())
		if(MessagePtr->MessageType == EMessageType::UStruct)
			return StaticCastSharedPtr<const TMessage>(MessagePtr);
		return MakeShareable(new TMessage(*MessagePtr));
	}
};
