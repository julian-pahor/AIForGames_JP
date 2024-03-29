#include "PathAgent.h"

namespace AIForGames
{
    PathAgent::PathAgent()
    {

    }

    void PathAgent::SetNode(Node* node)
    {
        m_currentNode = node;
        m_position.x = (node->position.x + 0.5f) * 30;
        m_position.y = (node->position.x + 0.5f) * 30;
    }

    void PathAgent::Update(float deltaTime)
    {
        if (m_path.empty())
        {
            return;
        }

        glm::float32 distance;

        glm::vec2 nodeWV;

        nodeWV.x = (m_path[m_currentIndex]->position.x + 0.5f) * 30;
        nodeWV.y = (m_path[m_currentIndex]->position.y + 0.5f) * 30;

        distance = glm::distance(m_position, nodeWV);

        glm::vec2 direction = glm::normalize(m_position - nodeWV);
        
        distance -= m_speed * deltaTime;

        if (distance > 0)
        {
            m_position -= m_speed * deltaTime * direction;
        }
        else
        {
            m_currentIndex++;

            if (m_currentIndex == m_path.size())
            {
                //m_position = m_path[m_currentIndex]->position;
                m_path.clear();
            }
            else
            {
                distance *= - 1; //inverse the direction back to a positive value
                
                direction = glm::normalize(m_position - nodeWV);

                m_position += m_speed * deltaTime * direction;
            }
        }
        
    }

    void PathAgent::GoToNode(Node* node)
    {
        m_path = NodeMap::DijkstrasSearch(m_currentNode, node);
        m_currentIndex = 0;
    }

    void PathAgent::Draw()
    {
        DrawCircleGradient(m_position.x, m_position.y, 10, RED, BLUE);
    }
}


