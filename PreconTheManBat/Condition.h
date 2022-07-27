#pragma once


namespace Precon
{
	class Agent;

	class Condition
	{
	public:
		virtual bool IsTrue(Agent* agent, float deltaTime) = 0;
	};
}

