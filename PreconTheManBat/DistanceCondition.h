#pragma once
#include "Condition.h"

namespace Precon
{
	class DistanceCondition : public Condition
	{
	private:
		float m_distance;
		bool m_lessThan;

	public:
		DistanceCondition(float d, bool lt) : m_distance(d), m_lessThan(lt) {}
		bool IsTrue(Agent* agent, float deltaTime) override;
	};
}


