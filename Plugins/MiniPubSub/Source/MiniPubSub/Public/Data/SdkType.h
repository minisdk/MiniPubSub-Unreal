
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
	public:
		static int GetNext();
	};
}
