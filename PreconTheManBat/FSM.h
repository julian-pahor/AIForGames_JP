#pragma once
#include <vector>

#include "Behaviour.h"

namespace Precon
{
	class State;

	class FSM : public Behaviour
	{
	private:
		std::vector<State*> m_states;

		State* m_currentState;
		State* m_newState;

	public:
		FSM(State* s) : m_currentState(s), m_newState(nullptr) {}
		virtual ~FSM();

		void Update(Agent* agent, float deltaTime) override;

		void AddState(State* s);

		void Enter(Agent* agent);
	};
}



