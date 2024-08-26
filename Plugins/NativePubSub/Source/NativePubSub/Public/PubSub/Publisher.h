#pragma once
#include "ReceivablePublisher.h"

enum class EPublisherType
{
	Android = 10000,
	IOS = 20000,
	Game = 30000
};

class NATIVEPUBSUB_API FPublisher final : public INode
{
private:
	const int NodeId;
	
public:
	virtual const int Id() const override{return NodeId;}

	FPublisher();
	virtual ~FPublisher() override;
	void Publish(TSharedPtr<const FMessage> Message) const;
};
