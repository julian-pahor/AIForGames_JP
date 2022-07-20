#pragma once

class Agent;

namespace AIForGames
{
	class Behaviour
	{
	public:
		virtual void Update(Agent* agent, float deltatime) = 0;
	};
}


