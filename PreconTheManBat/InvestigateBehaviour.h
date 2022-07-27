#pragma once
#include "Behaviour.h"
#include "Pathfinding.h"

namespace Precon
{
	class InvestigateBehaviour : public Behaviour
	{

		void Enter(Agent* agent) override;
		void Update(Agent* agent, float deltaTime) override;
		void Exit(Agent* agent) override;

	private:
		float m_speed;
		Node* targetNode;
	};
}


