#include <glm/glm.hpp>

#include "DistanceCondition.h"
#include "Agent.h"

namespace AIForGames
{
	bool DistanceCondition::IsTrue(Agent* agent)
	{
		return (glm::distance(agent->GetPathAgent().GetPosition(), agent->GetTarget()->GetPathAgent().GetPosition()) < m_distance) == m_lessThan;
	}
}

