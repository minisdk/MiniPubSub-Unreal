#pragma once

// using byte = unsigned char;
using byte = char;

DECLARE_DELEGATE_OneParam(FDelegate_Native_Data_Handler, const TArray<byte>&);
DECLARE_DELEGATE_OneParam(FDelegate_Native_Text_Handler, const FString&);

class INativeBridge
{
public:
	virtual ~INativeBridge()
	{
		
	};

	FDelegate_Native_Data_Handler DelNativeDataHandle;
	FDelegate_Native_Text_Handler DelNativeTextHandle;
	virtual void Send(const FString& Text) = 0;
};
