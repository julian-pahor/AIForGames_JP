#pragma once
#include "Behaviour.h"



namespace AIForGames
{
	class GotoPointBehaviour : public Behaviour

	{
	public:

		void Update(Agent* agent, float deltaTime) override;
	};
}


