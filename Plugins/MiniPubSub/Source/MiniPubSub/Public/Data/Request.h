#pragma once
#include "Serialization/JsonSerializerMacros.h"

namespace MiniPubSub
{
	struct FNodeInfo final : FJsonSerializable
	{
		int RequestOwnerId;
		int PublisherId;

		BEGIN_JSON_SERIALIZER
			JSON_SERIALIZE("requestOwnerId", RequestOwnerId);
			JSON_SERIALIZE("publisherId", PublisherId);
		END_JSON_SERIALIZER

		FNodeInfo(): RequestOwnerId(0), PublisherId(0)
		{}

		FNodeInfo(int InRequestOwnerId, int InPublisherId)
		: RequestOwnerId(InRequestOwnerId)
		, PublisherId(InPublisherId)
		{}
	};

	struct FRequestInfo final : FJsonSerializable
	{
		FNodeInfo NodeInfo;
		FString Key;
		FString ResponseKey;
		BEGIN_JSON_SERIALIZER
			JSON_SERIALIZE_OBJECT_SERIALIZABLE("nodeInfo", NodeInfo)
			JSON_SERIALIZE("key", Key);
			JSON_SERIALIZE("responseKey", ResponseKey);
		END_JSON_SERIALIZER

		FRequestInfo(): NodeInfo()
		{}

		FRequestInfo(const FNodeInfo& InNodeInfo, const FString& InKey, const FString& InResponseKey)
		: NodeInfo(InNodeInfo)
		, Key(InKey)
		, ResponseKey(InResponseKey){}
	};

	struct FResponseInfo
	{
		FString Key;
	};

	struct FRequest final : FJsonSerializable
	{
		FRequestInfo Info;
		FString Json;

		BEGIN_JSON_SERIALIZER
			JSON_SERIALIZE_OBJECT_SERIALIZABLE("info", Info)
			JSON_SERIALIZE("json", Json);
		END_JSON_SERIALIZER

		FString GetKey() const
		{
			return Info.Key;
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

		// TSharedPtr<FJsonObject> GetJsonObject() const
		// {
		// 	TSharedPtr<FJsonObject> JsonObject;
		// 	TSharedRef<TJsonReader<> > JsonReader = TJsonReaderFactory<>::Create(Json);
		// 	FJsonSerializer::Deserialize(JsonReader, JsonObject);
		// 	FJsonObjectConverter::JsonArrayStringToUStruct()
		// 	
		// 	return JsonObject;
		// }

		FRequest(const FRequestInfo& InInfo, const FString& InJson)
		: Info(InInfo)
		, Json(InJson)
		{}

		FRequest(const FNodeInfo& InNodeInfo, const FString& InKey, const FString& InJson, const FString& InResponseKey)
		: Info(FRequestInfo(InNodeInfo, InKey, InResponseKey))
		, Json(InJson)
		{}

		FResponseInfo GetResponseInfo() const
		{
			return FResponseInfo{Info.ResponseKey};
		}

	
	};
}
