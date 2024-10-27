#pragma once
#include "Publisher.h"
#include "Receiver.h"

class MINIPUBSUB_API FWatcher final : INode
{
private:
	const FPublisher Publisher;	
public:
	FWatcher()
	:Publisher(FPublisher()){}
	
	virtual const int Id() const override;
	void Watch(const FReceiveDelegate& ReceiveDelegate);
	void Unwatch();

	void Publish(const FMessage& Message) const;
};
