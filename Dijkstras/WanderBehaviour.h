#pragma once
#include "Behaviour.h"



namespace AIForGames
{
	class WanderBehaviour : public Behaviour
	{
	public:
		void Update(Agent* agent, float deltaTime) override;
		void Enter(Agent* agent) override;
	};
}


