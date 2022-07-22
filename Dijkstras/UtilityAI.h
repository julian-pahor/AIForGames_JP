#pragma once
#include <vector>

#include "Behaviour.h"

namespace AIForGames
{
	class UtilityAI : public Behaviour
	{
	private:
		std::vector<Behaviour*> m_behaviors;
		Behaviour* cBehaviour;

	public:
		~UtilityAI()
		{
			for (Behaviour* b : m_behaviors)
			{
				delete b;
			}
		}
		void Update(Agent* agent, float deltaTime) override;
		void AddBehaviour(Behaviour* b);
	};
}


