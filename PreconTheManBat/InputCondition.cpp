#include "InputCondition.h"

namespace Precon
{
	bool InputCondition::IsTrue(Agent* agent, float deltaTime)
	{
		return IsKeyPressed(m_inputKey);
	}
}