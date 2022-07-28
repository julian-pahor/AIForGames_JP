#include "PlayerBehaviour.h"
#include "Agent.h"

#include "raylib.h"



namespace Precon
{
	void PlayerBehaviour::Update(Agent* agent, float deltaTime)
	{

		if (IsKeyDown(KEY_W))
		{
			m_movement.y = -1;
		}
		else if (IsKeyDown(KEY_S))
		{
			m_movement.y = 1;
		}
		else
		{
			m_movement.y = 0;
		}

		if (IsKeyDown(KEY_A))
		{
			m_movement.x = -1;
		}
		else if (IsKeyDown(KEY_D))
		{
			m_movement.x = 1;
		}
		else
		{
			m_movement.x = 0;
		}

		agent->GetPathAgentPointer()->Translate(m_movement,agent->GetNodeMap(), deltaTime);

		
		
	}
}