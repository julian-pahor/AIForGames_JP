#include "GotoPointBehaviour.h"
#include "raylib.h"
#include "glm/glm.hpp"
#include "Agent.h"


namespace AIForGames
{

    void GotoPointBehaviour::Update(Agent* agent, float deltaTime)
    {
        // read mouseclicks, left for start node, end for right node
        if (IsMouseButtonPressed(0))
        {
            Vector2 mousePos = GetMousePosition();
            agent->SetNode(glm::vec2(mousePos.x, mousePos.y));
        }

        if (IsMouseButtonPressed(1))
        {
            Vector2 mousePos = GetMousePosition();
            agent->GoTo(glm::vec2(mousePos.x, mousePos.y));
        }
    }
}

