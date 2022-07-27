#pragma once
#include "Behaviour.h"



namespace Precon
{
	class WanderBehaviour : public Behaviour
	{
	public:
		void Update(Agent* agent, float deltaTime) override;
		void Enter(Agent* agent) override;
		void Exit(Agent* agent) override;
	};
}


