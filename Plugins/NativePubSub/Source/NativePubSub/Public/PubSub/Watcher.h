#pragma once
#include "Publisher.h"
#include "ReceivablePublisher.h"

class FWatcher final : IWatchable
{
private:
	const FPublisher Publisher;	
public:
	FWatcher()
	:Publisher(FPublisher()){}
	
	virtual const int Id() const override;
	virtual void Watch(const FReceiveDelegate& ReceiveDelegate) override;
	virtual void Unwatch() override;

	void Publish(TSharedPtr<const FMessage> Message) const;
};
