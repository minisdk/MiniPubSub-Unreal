// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JsonObjectConverter.h"

namespace MiniPubSub
{
	struct MINIPUBSUB_API FMessage
	{
		FString Json;

		explicit FMessage(const FString& InJson)
			: Json(InJson)
		{}

		template<typename DataType>
		static FMessage FromJsonSerializable(DataType Data)
		{
			static_assert(TIsDerivedFrom<DataType, FJsonSerializable>::Value, "DataType must be derived from FJsonSerializable");
			return FMessage(Data.ToJson());
		}

		static FMessage FromJsonObject(const TSharedRef<FJsonObject>& JsonObject)
		{
			// JSonWriter
			FString Json;
			TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&Json);
			FJsonSerializer::Serialize(JsonObject, Writer);
			return FMessage(Json);
		}
	};
}
