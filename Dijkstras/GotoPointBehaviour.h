#pragma once
#include "Behaviour.h"



namespace AIForGames
{
	class GotoPointBehaviour :
		public Behaviour
	{
		virtual void Update(Agent* agent, float deltaTime);
	};
}


