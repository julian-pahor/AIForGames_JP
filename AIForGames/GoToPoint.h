#pragma once
#include "Behaviour.h"

namespace AIForGames
{
	class GoToPoint : public Behaviour
	{
	public:
		virtual void Update(Agent* agent, float deltaTime);
	};
}


