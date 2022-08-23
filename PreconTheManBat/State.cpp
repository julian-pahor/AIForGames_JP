#include <vector>

#include "State.h"
#include "Behaviour.h"

namespace Precon
{
	State::State()
	{

	}

	State::State(Behaviour* b)
	{
		m_currentBehaviour = b;
		m_behaviours.push_back(b);

	}

	State::~State()
	{
		//we own the behaviours assigned to us
		for (Behaviour* b : m_behaviours)
		{
			delete b;
		}

		//we also own the COnditions ineach Transition
		//(but the states are references, so don't clean them up here)

		for (Transition t : m_transitions)
		{
			delete t.condition;
		}


	}

	void State::Enter(Agent* agent)
	{
		m_currentBehaviour->Enter(agent);
	}

	void State::Update(Agent* agent, float deltaTime)
	{
		for (Behaviour* b : m_behaviours)
		{
			b->Update(agent, deltaTime);
		}
	}
	void State::Exit(Agent* agent)
	{
		m_currentBehaviour->Exit(agent);
		//transition->condition->Exit()
	}

	std::vector<State::Transition> State::GetTransitions()
	{
		return m_transitions;
	}

	void State::AddTransition(Condition* c, State* s)
	{
		Transition t = { c, s };
		m_transitions.push_back(t);
	}


}