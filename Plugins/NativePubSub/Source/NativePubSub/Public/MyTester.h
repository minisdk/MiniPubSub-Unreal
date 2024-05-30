#pragma once

typedef char byte;

class FMyTester
{
public:
	NATIVEPUBSUB_API static void CallTest(const FString& Text);
	NATIVEPUBSUB_API static void CallByteTest(const TArray<byte>& Data);
};
