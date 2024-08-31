#pragma once

class MINIPUBSUB_API INode
{
public:
	virtual ~INode(){};
	virtual const int Id() const = 0;
};