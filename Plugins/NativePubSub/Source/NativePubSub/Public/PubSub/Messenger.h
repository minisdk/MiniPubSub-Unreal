#pragma once
#include "Publisher.h"
#include "ReceivablePublisher.h"

class NATIVEPUBSUB_API FMessenger final: ISubscribable
{
private:
	const FPublisher Publisher; 
	
public:
	FMessenger()
	:Publisher(FPublisher()){}

	virtual const int Id() const override;
	virtual void Subscribe(const FString& Key, const FReceiveDelegate& ReceiveDelegate) override;
	virtual void Unsubscribe(const FString& Key) override;

	void Publish(TSharedPtr<const FMessage> Message) const;
};
