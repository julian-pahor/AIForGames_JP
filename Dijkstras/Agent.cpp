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

    void Agent::GoTo(Node* node)
    {
        m_pathAgent.GoToNode(node);
    }

    void Agent::SetNode(Node* node)
    {
        m_pathAgent.SetNode(node);
    }

    void Agent::SetNode(glm::vec2 point)
    {
        Node* node = m_nodeMap->GetClosestNode(point);
        m_pathAgent.SetNode(node);
    }

    void Agent::SetSpeed(float speed)
    {
        m_pathAgent.SetSpeed(speed);
    }

    void Agent::Draw()
    {
        m_pathAgent.Draw();
    }
    bool Agent::PathComplete()
    {
        return m_pathAgent.GetPath().empty();
    }
    NodeMap* Agent::GetNodeMap()
    {
        return m_nodeMap;
    }
    Agent* Agent::GetTarget()
    {
        return m_targetAgent;
    }

    void Agent::SetTarget(Agent* agent)
    {
        m_targetAgent = agent;
    }

    glm::vec2 Agent::GetPosition()
    {
        return m_pathAgent.GetPosition();
    }
    
}
