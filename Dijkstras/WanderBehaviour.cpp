#include "WanderBehaviour.h"
#include "Agent.h"


namespace AIForGames
{
	void AIForGames::WanderBehaviour::Update(Agent* agent, float deltaTime)
	{
		if (agent->PathComplete())
		{
			agent->GoTo(agent->GetNodeMap()->GetRandomNode());
		}
	}
}

