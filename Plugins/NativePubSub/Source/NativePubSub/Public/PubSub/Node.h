#pragma once

class NATIVEPUBSUB_API INode
{
public:
	virtual ~INode(){};
	virtual const int Id() const = 0;
};