#pragma once

namespace AIForGames
{
	class Agent;

	class Behaviour
	{
	public:
		virtual void Update(Agent* agent, float deltatime) = 0;
	};
}


