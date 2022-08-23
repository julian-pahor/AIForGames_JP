#include "GoToBehaviour.h"
#include "raylib.h"
#include "Agent.h"


namespace Precon
{
    void GoToBehaviour::Enter(Agent* agent)
    {
        agent->SetColor(DARKBLUE);
        m_targetPosition = { 0 , 0 };
        m_speed = agent->GetPathAgent().GetSpeed();
        agent->SetSpeed(m_speed * 1.5f);

        Agent* target = agent->GetTarget();

        float dist = glm::distance(target->GetPathAgent().GetPosition(), m_targetPosition);
        
        m_targetPosition = target->GetPathAgent().GetPosition();

    }

    void GoToBehaviour::Update(Agent* agent, float deltaTime)
    {
        float cellSize = agent->GetNodeMap()->GetCellSize();

        glm::vec2 gPos = m_targetPosition;
        glm::vec2 pPos = { ((gPos.x + 0.5f) * cellSize), ((gPos.y + 0.5f) * cellSize) };
        agent->GoTo(pPos);

        if (IsKeyPressed(KEY_SPACE))
        {
            Enter(agent);
        }
    }
    void GoToBehaviour::Exit(Agent* agent)
    {
        agent->SetSpeed(m_speed);
    }
}

