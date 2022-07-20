#include "Agent.h"
#include "Behaviour.h"
#include "GotoPointBehaviour.h"

namespace AIForGames
{

    void Agent::Update(float deltaTime)
    {
        if (m_current)
            m_current->Update(this, deltaTime);
        m_pathAgent.Update(deltaTime);
    }

    void Agent::GoTo(glm::vec2 point)
    {
        Node* end = m_nodeMap->GetClosestNode(point);
        m_pathAgent.GoToNode(end);
    }

    void Agent::Draw()
    {
        m_pathAgent.Draw();
    }
}
