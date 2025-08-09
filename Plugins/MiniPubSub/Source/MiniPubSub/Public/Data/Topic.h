#pragma once
#include "SdkType.h"


namespace MiniPubSub
{
	struct FTopic final : FJsonSerializable
	{
		FString Key;
		int32 TargetNumber;

		BEGIN_JSON_SERIALIZER
			JSON_SERIALIZE("key", Key);
			JSON_SERIALIZE("target", TargetNumber);
		END_JSON_SERIALIZER

		FTopic(const FString& InKey, const ESdkType& InTarget)
		: Key(InKey)
		{
			TargetNumber = StaticCast<int32>(InTarget);
		}
		
		ESdkType GetTarget() const
		{
			return StaticCast<ESdkType>(TargetNumber);
		}
	};
}

const MiniPubSub::FTopic DefaultTopic("", MiniPubSub::ESdkType::Game); 
