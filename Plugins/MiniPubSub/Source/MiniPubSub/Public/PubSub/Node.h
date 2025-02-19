#pragma once

namespace MiniPubSub
{
	class MINIPUBSUB_API FNode
	{
		int NodeId;
	public:
		FNode();
		virtual ~FNode() = default;
		int GetId() const;
	};
}
