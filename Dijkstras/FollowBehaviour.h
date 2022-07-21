#pragma once
#include "Behaviour.h"
#include "raylib.h"
#include "glm/glm.hpp"

namespace AIForGames
{
	class FollowBehaviour : public Behaviour
	{
	public:

		void Enter(Agent* agent) override;
		void Update(Agent* agent, float deltaTime) override;

	private:
		glm::vec2 m_lastTargetPosition;
	};
}



