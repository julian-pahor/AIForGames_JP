#include <glm/glm.hpp>

#include "DistanceCondition.h"
#include "Agent.h"

namespace Precon
{
	bool DistanceCondition::IsTrue(Agent* agent, float deltaTime)
	{
		return (glm::distance(agent->GetPathAgent().GetPosition(), agent->GetTarget()->GetPathAgent().GetPosition()) < m_distance) == m_lessThan;
	}
}

