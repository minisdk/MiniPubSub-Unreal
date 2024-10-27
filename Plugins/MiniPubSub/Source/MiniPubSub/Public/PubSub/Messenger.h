#pragma once
#include "Publisher.h"
#include "Receiver.h"

class MINIPUBSUB_API FMessenger final: INode
{
private:
	const FPublisher Publisher; 
	
public:
	FMessenger()
	:Publisher(FPublisher()){}

	virtual const int Id() const override;
	void Subscribe(const FString& Key, const FReceiveDelegate& ReceiveDelegate);
	void Unsubscribe(const FString& Key);

	void Publish(const FMessage& Message) const;
};
