#include "HuntBehaviour.h"
#include "Agent.h"
#include "raylib.h"

namespace Precon
{
    void HuntBehaviour::Enter(Agent* agent)
    {
        agent->SetColor(RED);
        //agent->ResetPath();
        m_lastTargetPosition = { 0 , 0 };
    }

    void HuntBehaviour::Update(Agent* agent, float deltaTime)
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
    void HuntBehaviour::Exit(Agent* agent)
    {
        //agent->ResetPath();
    }
}

