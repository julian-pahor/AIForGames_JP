#pragma once

namespace Precon
{
	class Agent;

	class Behaviour
	{
	public:
		virtual void Enter(Agent* agent) {}
		virtual void Update(Agent* agent, float deltatime) = 0;
		virtual void Exit(Agent* agent) {}
	};
}


