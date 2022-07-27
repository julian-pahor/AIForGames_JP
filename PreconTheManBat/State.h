#pragma once
#include <vector>

namespace Precon
{
	class Behaviour;
	class Agent;
	class Condition;

	class State
	{

	public:
		struct Transition
		{
			Condition* condition;
			State* targetState;
		};

	private:
		std::vector<Behaviour*> m_behaviours;
		std::vector<Transition> m_transitions;
		Behaviour* m_currentBehaviour;

	public:
		State();
		State(Behaviour* b);
		~State();
		virtual void Enter(Agent* agent);
		virtual void Update(Agent* agent, float deltaTime);
		virtual void Exit(Agent* agent);

		std::vector<State::Transition> GetTransitions();
		void AddTransition(Condition* c, State* s);
	};
}


