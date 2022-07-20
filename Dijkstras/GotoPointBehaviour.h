#pragma once
#include "Behaviour.h"



namespace AIForGames
{
	class GotoPointBehaviour : public Behaviour

	{
		void Update(Agent* agent, float deltaTime) override;
	};
}


