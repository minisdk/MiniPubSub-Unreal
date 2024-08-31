#pragma once

typedef char byte;

class FMyTester
{
public:
	MINIPUBSUB_API static void CallTest(const FString& Text);
	MINIPUBSUB_API static void CallByteTest(const TArray<byte>& Data);
};
