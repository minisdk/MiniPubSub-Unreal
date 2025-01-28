#pragma once

// using byte = unsigned char;
using byte = char;

DECLARE_DELEGATE_TwoParams(FDelegate_Native_Handler, const FString&, const FString&);

class INativeBridge
{
public:
	virtual ~INativeBridge()
	{
		
	};
	
	FDelegate_Native_Handler NativeHandle;
	virtual void Send(const FString& Info, const FString& Data) = 0;
};
