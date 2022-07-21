#include "Pathfinding.h"
#include "raylib.h"
#include <iostream>
#include <list>


namespace AIForGames
{
    bool compare_G(Node* first, Node* second)
    {
        return (first->gScore < second->gScore);
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

    std::vector<Node*> NodeMap::DijkstrasSearch(Node* startNode, Node* endNode)
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
            openList.sort(compare_G);


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

                    if (std::find(openList.begin(), openList.end(), e.target) == openList.end())
                    {
                        e.target->gScore = gScore;
                        e.target->previous = cNode;
                        openList.push_front(e.target);
                    }
                    else if (gScore < e.target->gScore)
                    {
                        e.target->gScore = gScore;
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

                // create a node for anything but a '.' character
                m_nodes[x + m_width * y] = (tile == emptySquare) ? nullptr : new Node(x, y);
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
        // red color for the blocks
        Color cellColor;
        cellColor.a = 255;
        cellColor.r = 255;
        cellColor.g = 0;
        cellColor.b = 0;
        Color lineColor = SKYBLUE;

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
                else
                {
                    // draw the connections between the node and its neighbours
                    for (int i = 0; i < node->connections.size(); i++)
                    {
                        Node* other = node->connections[i].target;
                        DrawLine((x + 0.5f) * m_cellSize, (y + 0.5f) * m_cellSize,
                            (other->position.x + 0.5f) * m_cellSize,
                            (other->position.y + 0.5f) * m_cellSize,
                            lineColor);
                    }
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

