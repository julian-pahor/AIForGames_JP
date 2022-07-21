#pragma once
#include <vector>

#include "Behaviour.h"

namespace AIForGames
{
	class State;

	class FiniteStateMachine : public Behaviour
	{
	private:
		std::vector<State*> m_states;

		State* m_currentState;
		State* m_newState;

	public:
		FiniteStateMachine(State* s) : m_currentState(s), m_newState(nullptr) {} 
		virtual ~FiniteStateMachine();

		void Update(Agent* agent, float deltaTime) override;

		void AddState(State* s);

		void Enter(Agent* agent);
	};
}



