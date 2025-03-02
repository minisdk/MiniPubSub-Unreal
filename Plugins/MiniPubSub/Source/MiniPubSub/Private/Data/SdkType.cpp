#include "Data/SdkType.h"

#include "HAL/ThreadSafeCounter.h"
#include "Templates/UnrealTemplate.h"

constexpr int GJump(2);

int MiniPubSub::FIdCounter::GetNext()
{
	static FThreadSafeCounter Counter = FThreadSafeCounter(StaticCast<int>(ESdkType::Game));
	return Counter.Add(GJump);
}