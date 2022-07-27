#pragma once
#include "Behaviour.h"
#include "raylib.h"
#include "glm/glm.hpp"

namespace Precon
{
	class HuntBehaviour : public Behaviour
	{
	public:

		void Enter(Agent* agent) override;
		void Update(Agent* agent, float deltaTime) override;
		void Exit(Agent* agent) override;

	private:
		glm::vec2 m_lastTargetPosition;
	};
}



