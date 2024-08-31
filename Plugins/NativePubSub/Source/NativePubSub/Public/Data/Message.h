// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JsonObjectConverter.h"

/**
 * Message contains with key and data.
 * FMessage contains data as FJsonValue.
 * TMessage is template class. It contains UStruct object.
 */


/**
 * FMessage is base message class
 * Use FMessage::Create to create message
 * Parse json string using FMessage::ParseFrom.
 * Parsed message can be converted with TMessage.
 */
struct NATIVEPUBSUB_API FMessage
{
public:
	enum class EMessageType
	{
		FMessage,
		TMessage,
	};

	const EMessageType MessageType;  
	const FString Key;
	
protected:
	const TSharedPtr<FJsonValue> DataJson;


private:
	FMessage(const FString& Key)
	: MessageType(EMessageType::FMessage)
	, Key(Key)
	, DataJson(nullptr)
	{}

	FMessage(const FString& Key, const TSharedPtr<FJsonValue>& DataJson)
	: MessageType(EMessageType::FMessage)
	, Key(Key)
	, DataJson(DataJson)
	{}
	
protected:
	FMessage(const FString& Key, const EMessageType& MessageType)
	: MessageType(MessageType)
	, Key(Key)
	, DataJson(nullptr)
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

/**
 * TMessage contains UStruct data which can be serialized with json.
 * Use TMessage::Convert FMessage type message to TMessage.
 * 
 */
template<typename DataType>
struct NATIVEPUBSUB_API TMessage final :  FMessage
{
private:
	DataType *DataPtr;

	TMessage(const FString& Key, const DataType& Data)
	: FMessage(Key, EMessageType::TMessage)
	, DataPtr(new DataType(Data))
	{}

	explicit TMessage(const FMessage& Message)
	:FMessage(Message)
	{
		// DataJson's type have to EJson::Object 
		if(DataJson != nullptr && DataJson->Type == EJson::Object)
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
		// if message's original type is TMessage, static cast called  
		if(MessagePtr->MessageType == EMessageType::TMessage)
			return StaticCastSharedPtr<const TMessage>(MessagePtr);
		// If message' original type is FMessage, data is Deserialized from FMessage::DataJson
		return MakeShareable(new TMessage(*MessagePtr));
	}
};
