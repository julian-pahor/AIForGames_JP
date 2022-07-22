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
	void WanderBehaviour::Enter(Agent* agent)
	{
		agent->SetColor(PURPLE);
	}
	void WanderBehaviour::Exit(Agent* agent)
	{
		agent->ResetPath();
	}
	float WanderBehaviour::Evaluate(Agent* agent)
	{
		Agent* target = agent->GetTarget();

		float dist = glm::distance(target->GetPathAgent().GetPosition(), agent->GetPathAgent().GetPosition());

		float eval = dist;

		if (eval < 0)
		{
			eval = 0;
		}

		return eval;
	}
}

