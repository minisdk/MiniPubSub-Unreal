#include "MyTester.h"
#include "Bridge/MobileBridge.h"

void FMyTester::CallTest(const FString& Text)
{
	// UE_LOG(LogTemp, Warning, TEXT("Tester: %s"), *Text);
	// // FMobileBridge
	// FMobileBridge::Get()->DelNativeTextHandle.BindLambda([](const FString& Text)
	// {
	// 	UE_LOG(LogTemp, Display, TEXT("Native Test Call result : %s"), *Text);
	// });
	// FMobileBridge::Get()->Send(Text);
}

void FMyTester::CallByteTest(const TArray<byte>& Data)
{
	// FMobileBridge::Get()->DelNativeDataHandle.BindLambda([](const TArray<byte>& Data)
	// {
	// 	UE_LOG(LogTemp, Display, TEXT("Native Test Call result : %s"), Data.GetData());
	// });
}
