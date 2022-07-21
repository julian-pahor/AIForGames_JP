#include "FollowBehaviour.h"
#include "Agent.h"
#include "raylib.h"

namespace AIForGames
{
	void FollowBehaviour::Update(Agent* agent, float deltaTime)
	{
        // check if the agent has moved significantly from its last position
        // if so we want to repath towards it
        
        
        Agent* target = agent->GetTarget();

        float dist = glm::distance(target->GetPathAgent().GetPosition(), m_lastTargetPosition);
        float cellSize = agent->GetNodeMap()->GetCellSize();
        if (dist > 1)
        {
            m_lastTargetPosition = target->GetPathAgent().GetPosition();
            glm::vec2 gPos = m_lastTargetPosition;
            glm::vec2 pPos = { ((gPos.x + 0.5f) * cellSize), ((gPos.y + 0.5f) * cellSize) };
            agent->GoTo(pPos);
        }
        
	}
}

