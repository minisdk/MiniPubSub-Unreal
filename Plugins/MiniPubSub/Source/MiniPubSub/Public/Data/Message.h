#pragma once
#include "Payload.h"
#include "Topic.h"
#include "Serialization/JsonSerializerMacros.h"

namespace MiniPubSub
{
	struct FNodeInfo final : FJsonSerializable
	{
		int MessageOwnerId;
		int PublisherId;

		BEGIN_JSON_SERIALIZER
			JSON_SERIALIZE("messageOwnerId", MessageOwnerId);
			JSON_SERIALIZE("publisherId", PublisherId);
		END_JSON_SERIALIZER

		FNodeInfo(): MessageOwnerId(0), PublisherId(0)
		{}

		FNodeInfo(int InMessageOwnerId, int InPublisherId)
		: MessageOwnerId(InMessageOwnerId)
		, PublisherId(InPublisherId)
		{}
	};

	struct FMessageInfo final : FJsonSerializable
	{
		FNodeInfo NodeInfo;
		FTopic Topic;
		FTopic ReplyTopic;
		BEGIN_JSON_SERIALIZER
			JSON_SERIALIZE_OBJECT_SERIALIZABLE("nodeInfo", NodeInfo)
			JSON_SERIALIZE_OBJECT_SERIALIZABLE("topic", Topic);
			JSON_SERIALIZE_OBJECT_SERIALIZABLE("replyTopic", ReplyTopic);
		END_JSON_SERIALIZER

		FMessageInfo(): NodeInfo(), Topic(DefaultTopic), ReplyTopic(DefaultTopic)
		{
		}

		FMessageInfo(const FNodeInfo& InNodeInfo, const FTopic& InTopic, const FTopic& InReplyTopic)
		: NodeInfo(InNodeInfo)
		, Topic(InTopic)
		, ReplyTopic(InReplyTopic){}
	};

	struct FMessage final
	{
		FMessageInfo Info;
		FPayload Payload;

		FString GetKey() const
		{
			return Info.Topic.Key;
		}


		template<typename DataType>
		DataType ToJsonSerializable() const
		{
			static_assert(TIsDerivedFrom<DataType, FJsonSerializable>::Value, "DataType must be derived from FJsonSerializable");
			DataType Data = DataType();
			Data.FromJson(Payload.Json);
			return Data;
		}

		TSharedPtr<FJsonObject> ToJsonObject() const
		{
			TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
			TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(Payload.Json);
			FJsonSerializer::Deserialize(Reader, JsonObject);
			return JsonObject;
		}

		FMessage(const FMessageInfo& InInfo, const FString& InJson)
		: Info(InInfo)
		, Payload(InJson)
		{}

		FMessage(const FNodeInfo& InNodeInfo, const FTopic& InTopic, const FTopic& InReplyTopic, const FString& InJson)
		: Info(FMessageInfo(InNodeInfo, InTopic, InReplyTopic))
		, Payload(InJson)
		{}
		
	};
}
