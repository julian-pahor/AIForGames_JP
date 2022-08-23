#include "PathAgent.h"
#include <iostream>

namespace Precon
{
    glm::vec2 PathAgent::GetPosition()
    {
        return m_position;
    }

    Node* PathAgent::GetCurrentNode()
    {
        return m_currentNode;
    }

    void PathAgent::SetNode(Node* node)
    {
        if (node == nullptr)
        {
            return;
        }

        m_currentNode = node;
        m_position.x = node->position.x;
        m_position.y = node->position.y;
    }

    void PathAgent::Update(float deltaTime)
    {
        if (m_path.empty())
        {
            return;
        }

        glm::float32 distance;

        glm::vec2 nodeWV;


        nodeWV.x = m_path[m_currentIndex]->position.x;
        nodeWV.y = m_path[m_currentIndex]->position.y;

        distance = glm::distance(m_position, nodeWV);

        glm::vec2 direction = glm::normalize(m_position - nodeWV);

        distance -= m_speed * deltaTime;

        if (distance > 0)
        {
            m_position -= m_speed * deltaTime * direction;
        }
        else
        {

            m_currentNode = m_path[m_currentIndex];

            m_currentIndex++;

            if (m_currentIndex == m_path.size())
            {
                m_position = m_path[m_currentIndex - 1]->position;
                m_currentNode = m_path[m_currentIndex - 1];
                m_path.clear();
            }
            else
            {
                distance *= -1; //inverse the direction back to a positive value

                direction = glm::normalize(m_position - nodeWV);

                m_position += m_speed * deltaTime * direction;
            }
        }
    }

    void PathAgent::GoToNode(Node* node)
    {
        m_path = NodeMap::AStarSearch(m_currentNode, node);
        m_currentIndex = 1;
    }

    void PathAgent::Draw(Color color)
    {
        //Hard coded for cellsize calculation, need to fix

        DrawCircle((m_position.x + 0.5f) * 25, (m_position.y + 0.5f) * 25, 10, color);


        //Drawing of Path, useful for debugging but not needed for gameplay

        /*if (m_path.size() > 1)
        {
            for (int i = 0; i < m_path.size() - 1; i++)
            {
                DrawLine((m_path[i]->position.x + 0.5f) * 25,
                    (m_path[i]->position.y + 0.5f) * 25,
                    (m_path[i + 1]->position.x + 0.5f) * 25,
                    (m_path[i + 1]->position.y + 0.5f) * 25,
                    RED);
            }
        }*/
    }

    void PathAgent::ClearPath()
    {
        m_path.clear();
    }

    std::vector<Node*> PathAgent::GetPath()
    {
        return m_path;
    }

    void PathAgent::Translate(glm::vec2 movement,NodeMap* nodeMap, float deltaTime)
    {
        //being passed a vector2 for standard WASD movement control
        //0,1 = w
        //0,-1 = s
        //1,0 = d
        //-1, 0 == a
        
        glm::vec2 worldPos = { (m_position.x + 0.5f) * 25, (m_position.y + 0.5f) * 25 };

        Node* closestNode = nodeMap->GetClosestNode(worldPos);

        m_pushBack -= deltaTime;

        if (!closestNode)
        {
            m_pushBack = m_pushBackTimer;
            m_position += m_speed * -movement * deltaTime;
        }
        else if(closestNode && m_pushBack < 0)
        {
            m_currentNode = closestNode;
            m_position += m_speed * movement * deltaTime;
        }
        

        
    }
}


