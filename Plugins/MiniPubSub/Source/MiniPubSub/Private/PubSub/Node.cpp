#include "PubSub/Node.h"

#include "Data/SdkType.h"


MiniPubSub::FNode::FNode()
{
	FIdCounter GIdCounter = FIdCounter();
	NodeId = GIdCounter.GetNext();
}

int MiniPubSub::FNode::GetId() const
{
	return NodeId;
}
