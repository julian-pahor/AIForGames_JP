#include "FSM.h"
#include "State.h"
#include "Condition.h"

namespace Precon
{
	FSM::~FSM()
	{
		//go through and delete all states within the FSM
		for (State* s : m_states)
		{
			delete s;
		}
	}

	void FSM::Update(Agent* agent, float deltaTime)
	{
		State* newState = nullptr;

		//check the current states transitions
		for (State::Transition t : m_currentState->GetTransitions())
		{
			if (t.condition->IsTrue(agent, deltaTime))
			{
				newState = t.targetState;
			}
		}

		//if we've changed state, clean up the old one and initialise the new one
		if (newState != nullptr && newState != m_currentState)
		{
			for (State::Transition t : m_currentState->GetTransitions())
			{
				t.condition->Exit(agent);
			}

			m_currentState->Exit(agent);
			m_currentState = newState;
			m_currentState->Enter(agent);
		}

		//update the current state
		m_currentState->Update(agent, deltaTime);
	}

	void FSM::AddState(State* s)
	{
		m_states.push_back(s);
	}

	void FSM::Enter(Agent* agent)
	{
		m_currentState->Enter(agent);
	}
}