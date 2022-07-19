#pragma once

#include "Pathfinding.h"

#include <glm/glm.hpp>
#include <vector>
#include <string>
#include "raylib.h"

namespace AIForGames
{
    class PathAgent
    {
    private:

        glm::vec2 m_position;

        std::vector<Node*> m_path;
        int m_currentIndex = 0;
        Node* m_currentNode = nullptr;

        float m_speed = 15;

        //Texture2D m_sprite;

    public:

        PathAgent();

        void SetSpeed(float speed) { m_speed = speed; }
        void SetNode(Node* node);

        void Update(float deltaTime);
        void GoToNode(Node* node);
        void Draw();

    };
}



