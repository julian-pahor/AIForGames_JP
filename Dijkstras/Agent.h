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
        void SetNode(Node* node);
        void SetNode(glm::vec2 point);
        void SetSpeed(float speed);
        void Draw();

    private:
        PathAgent m_pathAgent;
        Behaviour* m_current;
        NodeMap* m_nodeMap;
        Color m_color;
    };
}


