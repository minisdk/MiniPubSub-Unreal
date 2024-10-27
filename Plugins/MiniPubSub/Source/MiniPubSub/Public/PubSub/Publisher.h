#pragma once
#include "Node.h"
#include "Data/Message.h"

enum class MINIPUBSUB_API EPublisherType
{
	Android = 10000,
	IOS = 20000,
	Game = 30000
};

class MINIPUBSUB_API FPublisher final : public INode
{
private:
	const int NodeId;
	
public:
	virtual const int Id() const override{return NodeId;}

	FPublisher();
	virtual ~FPublisher() override;
	void Publish(const FMessage& Message) const;
};
