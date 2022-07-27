#pragma once
#include "Condition.h"
#include <raylib.h>

namespace Precon
{
	class InputCondition : public Condition
	{
	private:
		KeyboardKey m_inputKey;

	public:
		InputCondition(KeyboardKey key) : m_inputKey(key) {}
		bool IsTrue(Agent* agent, float deltaTime) override;
	};
}


