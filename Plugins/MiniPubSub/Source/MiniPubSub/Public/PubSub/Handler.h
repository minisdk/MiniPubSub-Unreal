#pragma once
#include "Data/Message.h"
#include "Data/Payload.h"

namespace MiniPubSub
{
	DECLARE_DELEGATE_RetVal_OneParam(FPayload /*RetVal*/, FHandleDelegate, const FMessage&)
	
	struct FHandler final
	{
		int NodeId;
		FString Key;
		ESdkType Target;
		FHandleDelegate HandleDelegate;

	public:
		FHandler(const int& Id, const FString& InKey, const ESdkType& InTarget, const FHandleDelegate& Delegate)
		: NodeId(Id)
		, Key(InKey)
		, Target(InTarget)
		, HandleDelegate(Delegate)
		{}

		bool CanInvoke(FMessageInfo Info) const
		{
			return NodeId != Info.NodeInfo.PublisherId && Target == Info.Topic.GetTarget();
		}
	};

}
