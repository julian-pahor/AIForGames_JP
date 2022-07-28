#include "Agent.h"
#include "Behaviour.h"

namespace Precon
{
    Agent::Agent(NodeMap* _nodeMap, Behaviour* _behaviour)
    {
        m_current = _behaviour;
        m_nodeMap = _nodeMap;
        m_color = RED;
        m_current->Enter(this);
    }

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
        m_pathAgent.Draw(m_color);
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

    PathAgent Agent::GetPathAgent()
    {
        return m_pathAgent;
    }

    PathAgent* Agent::GetPathAgentPointer()
    {
        return &m_pathAgent;
    }

    void Agent::ResetPath()
    {
        m_pathAgent.ClearPath();
    }



}
