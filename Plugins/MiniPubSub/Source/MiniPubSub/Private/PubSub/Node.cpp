#include "PubSub/Node.h"

#include "Data/SdkType.h"


MiniPubSub::FNode::FNode()
{
	NodeId = FIdCounter::GetNext();
}

int MiniPubSub::FNode::GetId() const
{
	return NodeId;
}
