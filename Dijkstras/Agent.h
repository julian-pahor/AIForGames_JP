#pragma once
#include "glm/glm.hpp"
#include "raylib.h"
#include "PathAgent.h"


namespace AIForGames
{
    class Behaviour;

    class Agent

    {
    public:
        Agent() {}
        Agent(NodeMap* _nodeMap, Behaviour* _behaviour) : m_current(_behaviour), m_nodeMap(_nodeMap), m_color({ 255, 255, 0, 255 }) {}
        ~Agent() { delete m_current; }

        void Update(float deltaTime);
        void GoTo(glm::vec2 point);
        void GoTo(Node* node);
        void SetNode(Node* node);
        void SetNode(glm::vec2 point);
        void SetSpeed(float speed);
        void Draw();
        bool PathComplete();

        NodeMap* GetNodeMap();
        Agent* GetTarget();
        void SetTarget(Agent* agent);
        glm::vec2 GetPosition();
        

    private:
        Agent* m_targetAgent = nullptr;
        PathAgent m_pathAgent;
        Behaviour* m_current;
        NodeMap* m_nodeMap;
        Color m_color;
    };
}


