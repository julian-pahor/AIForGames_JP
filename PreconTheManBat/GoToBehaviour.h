#pragma once
#include "Behaviour.h"
#include "glm/glm.hpp"



namespace Precon
{
	class GoToBehaviour : public Behaviour

	{
	private:
		float m_speed;
		glm::vec2 m_targetPosition;

	public:
		void Enter(Agent* agent) override;
		void Update(Agent* agent, float deltaTime) override;
		void Exit(Agent* agent) override;
	};
}


