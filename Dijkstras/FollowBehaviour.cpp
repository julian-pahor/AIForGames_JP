#include "FollowBehaviour.h"
#include "Agent.h"
#include "raylib.h"

namespace AIForGames
{
    void FollowBehaviour::Enter(Agent* agent)
    {
        agent->SetColor(RED);
        //agent->ResetPath();
        m_lastTargetPosition = { 0 , 0 };
    }

    void FollowBehaviour::Update(Agent* agent, float deltaTime)
	{
        // check if the agent has moved significantly from its last position
        // if so we want to repath towards it

        Agent* target = agent->GetTarget();

        float dist = glm::distance(target->GetPathAgent().GetPosition(), m_lastTargetPosition);
        float cellSize = agent->GetNodeMap()->GetCellSize();
        if (dist > 1) //1 value represents 1 grid 
        {
            m_lastTargetPosition = target->GetPathAgent().GetPosition();
            glm::vec2 gPos = m_lastTargetPosition;
            glm::vec2 pPos = { ((gPos.x + 0.5f) * cellSize), ((gPos.y + 0.5f) * cellSize) };
            agent->GoTo(pPos);
        }
	}
    void FollowBehaviour::Exit(Agent* agent)
    {
        agent->ResetPath();
    }
    float FollowBehaviour::Evaluate(Agent* agent)
    {
        Agent* target = agent->GetTarget();
        float dist = glm::distance(target->GetPathAgent().GetPosition(), agent->GetPathAgent().GetPosition());

        float eval = 10 - dist; //represents 10 grid spaces 

        if (eval < 0)
        {
            eval = 0;
        }

        return eval;
    }
}

