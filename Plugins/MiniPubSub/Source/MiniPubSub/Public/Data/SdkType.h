
#pragma once

namespace MiniPubSub
{
	enum class ESdkType
	{
		Native = 0,
		Game = 1
	};

	class FIdCounter
	{
		// int Amount = 2;
		// FThreadSafeCounter Counter = FThreadSafeCounter(StaticCast<int>(ESdkType::Game) - Amount);
	public:
		static int GetNext();
		// {
		// 	return Counter.Add(Amount);
		// }
	};
}
