#pragma once

namespace AIForGames
{
	class Agent;

	class Behaviour
	{
	public:
		virtual void Enter(Agent* agent) {}
		virtual void Update(Agent* agent, float deltatime) = 0;
		virtual void Exit(Agent* agent) {}

		//Used by UtilityAI to determine which behaviour to do
		virtual float Evaluate(Agent* agent) { return 0.0f; }
	};
}


