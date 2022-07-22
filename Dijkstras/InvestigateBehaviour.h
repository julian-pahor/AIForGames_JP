#pragma once
#include "Behaviour.h"
#include "Pathfinding.h"

namespace AIForGames
{
	class InvestigateBehaviour : public Behaviour
	{

		void Enter(Agent* agent) override;
		void Update(Agent* agent, float deltaTime) override;
		void Exit(Agent* agent) override;

	private:
		Node* targetNode;
	};
}


