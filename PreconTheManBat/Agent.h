#pragma once
#include "glm/glm.hpp"
#include "raylib.h"
#include "PathAgent.h"


namespace Precon
{
    class Behaviour;

    class Agent

    {
    public:
        Agent() {}
        Agent(NodeMap* _nodeMap, Behaviour* _behaviour);
        ~Agent() { delete m_current; }

        void Update(float deltaTime);
        void SetColor(Color color) { m_color = color; }
        void GoTo(glm::vec2 point);
        void GoTo(Node* node);
        void SetNode(Node* node);
        void SetNode(glm::vec2 point);
        void SetSpeed(float speed);
        void Draw();
        bool PathComplete();
        
        bool CheckWin();

        NodeMap* GetNodeMap();
        Agent* GetTarget();
        void SetTarget(Agent* agent);
        PathAgent GetPathAgent();
        PathAgent* GetPathAgentPointer();

        void ResetPath();


    private:
        Agent* m_targetAgent = nullptr;
        PathAgent m_pathAgent;
        Behaviour* m_current;
        NodeMap* m_nodeMap;
        Color m_color;
    };
}


