#include "WanderBehaviour.h"
#include "Agent.h"


namespace Precon
{
	void WanderBehaviour::Update(Agent* agent, float deltaTime)
	{
		if (agent->PathComplete())
		{
			agent->GoTo(agent->GetNodeMap()->GetRandomNode());
		}
	}
	void WanderBehaviour::Enter(Agent* agent)
	{
		agent->SetColor(PURPLE);
	}
	void WanderBehaviour::Exit(Agent* agent)
	{
		agent->ResetPath();
	}
}

