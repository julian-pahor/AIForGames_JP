#include "TimerCondition.h"

namespace Precon
{
	bool TimerCondition::IsTrue(Agent* agent, float deltaTime)
	{
		m_timer -= deltaTime;

		bool check = false;

		if (m_timer < 0)
		{
			check = true;
			m_timer = m_cooldown;
		}

		return check;
	}
}

