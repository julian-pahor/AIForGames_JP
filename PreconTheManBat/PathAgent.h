#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "Pathfinding.h"
#include "raylib.h"

namespace Precon
{
    class PathAgent
    {
    private:

        glm::vec2 m_position;

        std::vector<Node*> m_path;
        int m_currentIndex;
        Node* m_currentNode;

        float m_speed;

    public:
        glm::vec2 GetPosition();
        Node* GetCurrentNode();
        void SetNode(Node* node);
        void SetSpeed(float speed) { m_speed = speed; }
        float GetSpeed() { return m_speed; }
        void Update(float deltaTime);
        void GoToNode(Node* node);
        void Draw(Color color);
        void ClearPath();
        std::vector<Node*> GetPath();

        void Translate(glm::vec2 movement, float deltaTime);
    };
}


