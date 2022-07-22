#include "InvestigateBehaviour.h"
#include "Agent.h"


namespace AIForGames
{
	void InvestigateBehaviour::Enter(Agent* agent)
	{
		agent->SetColor(GREEN);
		agent->SetSpeed(2);
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
		agent->SetSpeed(4);
		agent->ResetPath();
	}
}
