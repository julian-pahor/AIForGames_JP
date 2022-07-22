#include "UtilityAI.h"

namespace AIForGames
{
	void UtilityAI::Update(Agent* agent, float deltaTime)
	{
		float bestEval = 0;
		Behaviour* newBehaviour = nullptr;

		for (Behaviour* b : m_behaviors)
		{
			float eval = b->Evaluate(agent);

			if (eval > bestEval)
			{
				bestEval = eval;
				newBehaviour = b;
			}
		}

		if (newBehaviour != nullptr && newBehaviour != cBehaviour)
		{
			if (cBehaviour)
			{
				cBehaviour->Exit(agent);
			}

			cBehaviour = newBehaviour;
			cBehaviour->Enter(agent);
		}

		cBehaviour->Update(agent, deltaTime);
	}
	void UtilityAI::AddBehaviour(Behaviour* b)
	{
		m_behaviors.push_back(b);
	}
}

