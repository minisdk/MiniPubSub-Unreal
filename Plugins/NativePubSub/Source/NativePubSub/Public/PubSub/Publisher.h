#pragma once
#include "ReceivablePublisher.h"

class NATIVEPUBSUB_API FPublisher : public INode
{
public:
	virtual ~FPublisher() override;
	void Publish(const FMessage& Message);
};
