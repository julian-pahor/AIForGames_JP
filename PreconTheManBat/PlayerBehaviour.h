#pragma once
#include "Behaviour.h"
#include "glm/glm.hpp"

namespace Precon
{
	class PlayerBehaviour : public Behaviour
	{
	private:
		glm::vec2 m_movement;

	public:
		void Update(Agent* agent, float deltaTime) override;
	};

}

