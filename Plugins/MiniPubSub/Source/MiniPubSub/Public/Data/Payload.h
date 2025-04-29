// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Policies/CondensedJsonPrintPolicy.h"

namespace MiniPubSub
{
	struct MINIPUBSUB_API FPayload
	{
		FString Json;

		explicit FPayload(const FString& InJson)
			: Json(InJson)
		{}

		template<typename DataType>
		static FPayload FromJsonSerializable(DataType Data)
		{
			static_assert(TIsDerivedFrom<DataType, FJsonSerializable>::Value, "DataType must be derived from FJsonSerializable");
			return FMessage(Data.ToJson());
		}

		static FPayload FromJsonObject(const TSharedRef<FJsonObject>& JsonObject)
		{
			// JSonWriter
			FString Json;
			TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&Json);
			FJsonSerializer::Serialize(JsonObject, Writer);
			return FPayload(Json);
		}

		template<typename DataType>
		DataType ToJsonSerializable() const
		{
			static_assert(TIsDerivedFrom<DataType, FJsonSerializable>::Value, "DataType must be derived from FJsonSerializable");
			DataType Data = DataType();
			Data.FromJson(Json);
			return Data;
		}

		TSharedPtr<FJsonObject> ToJsonObject() const
		{
			TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
			TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(Json);
			FJsonSerializer::Deserialize(Reader, JsonObject);
			return JsonObject;
		}
	};
}
