#include "Agent.h"
#include "Behaviour.h"

void AIForGames::Agent::Update(float deltaTime)
{
	if (m_current)
	{
		m_current->Update(this, deltaTime);
	}

	m_pathAgent.Update(deltaTime);
}

void AIForGames::Agent::Draw()
{
	m_pathAgent.Draw();
}

void AIForGames::Agent::GoTo(glm::vec2 point)
{
	Node* end = m_nodeMap->GetClosestNode(point);
	m_pathAgent.GoToNode(end);
}
