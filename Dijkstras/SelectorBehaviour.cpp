#include "SelectorBehaviour.h"
#include "Agent.h"

#include "raylib.h"
#include "glm/glm.hpp"

namespace AIForGames
{
	void SelectorBehaviour::Update(Agent* agent, float deltaTime)
	{
		//if distance between this agent and its target is less than 5 grid spaces
		if (glm::distance(agent->GetPathAgent().GetPosition(), agent->GetTarget()->GetPathAgent().GetPosition()) < 5)
		{
			SetBehaviour(m_b1, agent);
			agent->SetColor(ORANGE);
		}
		else
		{
			SetBehaviour(m_b2, agent);
			agent->SetColor(DARKPURPLE);
		}


		m_selected->Update(agent, deltaTime);
	}

	void SelectorBehaviour::SetBehaviour(Behaviour* b, Agent* agent)
	{
		if (m_selected != b)
		{
			m_selected = b;
			agent->ResetPath();
		}
	}
}
