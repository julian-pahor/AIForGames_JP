#include "GoToPoint.h"
#include "raylib.h"
#include "glm/glm.hpp"
#include "Agent.h"

void AIForGames::GoToPoint::Update(Agent* agent, float deltaTime)
{
	//read mouseclicks, left for start node, end for right node

	if (IsMouseButtonPressed(0))
	{
		Vector2 mousePos = GetMousePosition();
		agent->GoTo(glm::vec2(mousePos.x, mousePos.y));
	}
}
