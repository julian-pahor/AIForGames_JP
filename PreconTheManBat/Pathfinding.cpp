#include "Pathfinding.h"
#include "glm/glm.hpp"
#include "raylib.h"
#include <iostream>
#include <list>


namespace Precon
{
    bool compare_F(Node* first, Node* second)
    {
        return (first->fScore < second->fScore);
    }

    float Heuristic(Node* first, Node* second)
    {
        return glm::distance(first->position, second->position);
    }

    Node* NodeMap::GetRandomNode()
    {
        Node* node = nullptr;

        while (node == nullptr)
        {
            int x = GetRandomValue(0, 1000) % m_width;
            int y = GetRandomValue(0, 1000) % m_height;
            node = GetNode(x, y);
        }

        return node;
    }

    Node* NodeMap::GetNearbyNode(Node* target)
    {
        Node* targetNode = target;
        Node* node = nullptr;

        bool found = false;

        while (!found)
        {
            found = true;

            node = GetRandomNode();

            if (Heuristic(node, targetNode) > 2.5f)
            {
                found = false;
            }
        }

        return node;
    }



    std::vector<Node*> NodeMap::AStarSearch(Node* startNode, Node* endNode)
    {
        std::vector<Node*> dPath;

        if (endNode == nullptr)
        {
            return dPath;
        }

        if (startNode == nullptr || endNode == nullptr)
        {
            throw std::runtime_error("Start or End node = nullptr");
        }

        if (startNode == endNode)
        {
            return dPath;
        }

        startNode->gScore = 0;
        startNode->previous = nullptr;

        std::list<Node*> openList, closedList;

        openList.push_front(startNode);

        Node* cNode;

        while (!openList.empty())
        {
            openList.sort(compare_F);


            cNode = openList.front();

            if (cNode == endNode)
            {
                break;
            }

            openList.remove(cNode);
            closedList.push_front(cNode);

            for (Edge e : cNode->connections)
            {
                if (std::find(closedList.begin(), closedList.end(), e.target) == closedList.end())
                {
                    float gScore = cNode->gScore + e.cost;
                    float hScore = Heuristic(e.target, endNode);
                    float fScore = gScore + hScore;

                    if (std::find(openList.begin(), openList.end(), e.target) == openList.end())
                    {
                        e.target->gScore = gScore;
                        e.target->fScore = fScore;
                        e.target->previous = cNode;
                        openList.push_front(e.target);
                    }
                    else if (fScore < e.target->fScore)
                    {
                        e.target->gScore = gScore;
                        e.target->fScore = fScore;
                        e.target->previous = cNode;
                    }
                }
            }
        }

        cNode = endNode;

        while (cNode != nullptr)
        {
            dPath.push_back(cNode);
            cNode = cNode->previous;
        }

        std::reverse(dPath.begin(), dPath.end());

        return dPath;
    }

    void NodeMap::Initialise(std::vector<std::string> asciiMap, int cellSize)
    {
        m_cellSize = cellSize;
        const char emptySquare = '0';
        const char entrySquare = '2';
        const char exitSquare = '3';

        // assume all strings are the same length, so we'll size the map according
        // to the number of strings and the length of the first one
        m_height = asciiMap.size();
        m_width = asciiMap[0].size();

        m_nodes = new Node * [m_width * m_height];

        // loop over the strings, creating Node entries as we go
        for (int y = 0; y < m_height; y++)
        {
            std::string& line = asciiMap[y];
            // report to the use that you have a mis-matched string length
            if (line.size() != m_width)
                std::cout << "Mismatched line #" << y << " in ASCII map (" << line.size() << " instead of " << m_width << ")" << std::endl;

            for (int x = 0; x < m_width; x++)
            {
                // get the x-th character, or return an empty node if the string         
                // isn't long enough
                char tile = x < line.size() ? line[x] : emptySquare;

                switch (tile)
                {
                case emptySquare:
                    m_nodes[x + m_width * y] = nullptr;
                    break;
                case entrySquare:
                    m_nodes[x + m_width * y] = new Node(x, y, 2);
                    break;
                case exitSquare:
                    m_nodes[x + m_width * y] = new Node(x, y, 3);
                    break;
                default:
                    m_nodes[x + m_width * y] = new Node(x, y);
                    break;
                }
            }
        }

        for (int y = 0; y < m_height; y++)
        {
            for (int x = 0; x < m_width; x++)
            {
                Node* node = GetNode(x, y);
                if (node)
                {
                    // see if there's a node to our west, checking for array overruns      
                    // first if we're on the west-most edge
                    Node* nodeWest = x == 0 ? nullptr : GetNode(x - 1, y);
                    if (nodeWest)
                    {
                        node->ConnectTo(nodeWest, 1); // TODO weights
                        nodeWest->ConnectTo(node, 1);
                    }

                    // see if there's a node south of us, checking for array index
                    // overruns again
                    Node* nodeSouth = y == 0 ? nullptr : GetNode(x, y - 1);
                    if (nodeSouth)
                    {
                        node->ConnectTo(nodeSouth, 1);
                        nodeSouth->ConnectTo(node, 1);
                    }
                }
            }
        }
    }

    void NodeMap::Draw()
    {
        //Color for the blocks
        Color cellColor = DARKBROWN;
        Color pathColor = GREEN;
        Color entryColor = BLUE;
        Color exitColor = RED;


        for (int y = 0; y < m_height; y++)
        {
            for (int x = 0; x < m_width; x++)
            {
                Node* node = GetNode(x, y);
                if (node == nullptr)
                {
                    // draw a solid block in empty squares without a navigation node
                    DrawRectangle((int)(x * m_cellSize), (int)(y * m_cellSize),
                        (int)m_cellSize - 1, (int)m_cellSize - 1, cellColor);
                }
                else if (node->entryNode)
                {
                    node->nodeColor = entryColor;
                    DrawRectangle((int)(x * m_cellSize), (int)(y * m_cellSize),
                        (int)m_cellSize - 1, (int)m_cellSize - 1, node->nodeColor);
                }
                else if (node->exitNode)
                {
                    node->nodeColor = exitColor;
                    DrawRectangle((int)(x * m_cellSize), (int)(y * m_cellSize),
                        (int)m_cellSize - 1, (int)m_cellSize - 1, node->nodeColor);
                }
                else
                {
                    if (node->nodeColor.a == 255)
                    {
                        pathColor.a = GetRandomValue(75, 115);
                        node->nodeColor = pathColor;
                    }

                    DrawRectangle((int)(x * m_cellSize), (int)(y * m_cellSize),
                        (int)m_cellSize - 1, (int)m_cellSize - 1, node->nodeColor);
                }
            }
        }
    }

    void Node::ConnectTo(Node* other, float cost)
    {
        connections.push_back(Edge(other, cost));
    }

    Node* NodeMap::GetClosestNode(glm::vec2 worldPos)
    {
        int i = (int)(worldPos.x / m_cellSize);
        if (i < 0 || i >= m_width) return nullptr;

        // do the same for y
        int j = (int)(worldPos.y / m_cellSize);
        if (j < 0 || j >= m_height) return nullptr;

        return GetNode(i, j);
    }
    float NodeMap::GetCellSize()
    {
        return m_cellSize;
    }
}

