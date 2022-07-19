#pragma once
#include "PathAgent.h"
#include "Pathfinding.h"


namespace AIForGames
{
	class Behaviour;

	class Agent
	{
	public:
		Agent() {}
		Agent(NodeMap* _nodemap, Behaviour* _behaviour) : m_current(_behaviour), m_nodeMap(_nodemap),
			m_color({ 255, 255, 0, 255 })
		{
			m_pathAgent.SetSpeed(64);

		}
		~Agent() { delete m_current; }

		void Update(float deltaTime);
		void Draw();
		void GoTo(glm::vec2 point);

	private:
		PathAgent m_pathAgent;
		Behaviour* m_current;
		NodeMap* m_nodeMap;
		Color m_color;

	};
}


