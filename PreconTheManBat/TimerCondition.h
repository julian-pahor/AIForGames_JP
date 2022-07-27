#pragma once
#include "Condition.h"

namespace Precon
{
	class TimerCondition : public Condition
	{
	private:
		float m_timer;
		float m_cooldown;

	public:
		TimerCondition(float t) : m_timer(t), m_cooldown(t) {}
		bool IsTrue(Agent* agent, float deltaTime) override;

	};
}


