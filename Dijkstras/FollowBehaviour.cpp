#include "FollowBehaviour.h"
#include "Agent.h"

namespace AIForGames
{
	void FollowBehaviour::Update(Agent* agent, float deltaTime)
	{

        // check if the agent has moved significantly from its last position
        // if so we want to repath towards it
        Agent* target = agent->GetTarget();

        //float dist = glm::distance(target->GetPosition(), m_lastTargetPosition);

        //if (dist > agent->GetNodeMap()->GetCellSize())
        //{
        //    m_lastTargetPosition = target->GetPosition();
        //    agent->GoTo(m_lastTargetPosition);
        //}

        agent->GoTo(target->GetPosition());
	}
}

