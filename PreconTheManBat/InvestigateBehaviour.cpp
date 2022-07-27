#include "InvestigateBehaviour.h"
#include "Agent.h"


namespace Precon
{
	void InvestigateBehaviour::Enter(Agent* agent)
	{
		agent->SetColor(GREEN);
		m_speed = agent->GetPathAgent().GetSpeed();
		agent->SetSpeed(m_speed / 2.f);
		targetNode = agent->GetPathAgent().GetCurrentNode();
		agent->ResetPath();
	}

	void InvestigateBehaviour::Update(Agent* agent, float deltaTime)
	{
		if (agent->PathComplete())
		{
			agent->GoTo(agent->GetNodeMap()->GetNearbyNode(targetNode));
		}
	}

	void InvestigateBehaviour::Exit(Agent* agent)
	{
		agent->SetSpeed(m_speed);
		agent->ResetPath();
	}
}
