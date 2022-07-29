#pragma once

#include <glm/glm.hpp>
#include <raylib.h>
#include <vector>
#include <string>

namespace Precon
{
    struct Node;

    //Edge node used to store data on connecting nodes and their travel cost between eachother
    struct Edge
    {
        Edge() { target = nullptr; cost = 0; }
        Edge(Node* _node, float _cost) : target(_node), cost(_cost) {}

        Node* target;
        float cost;
    };

    struct Node
    {
        Node(float x, float y) : position(x, y) { }
        Node(float x, float y, float type) : position(x, y)
        {
            if (type == 2)
            {
                entryNode = true;
            }
            else if (type == 3)
            {
                exitNode = true;
            }
        }

        glm::vec2 position;
        std::vector<Edge> connections;

        float gScore;
        float hScore;
        float fScore;
        Color nodeColor = WHITE;
        Node* previous = nullptr;
        
        bool entryNode = false;
        bool exitNode = false;

        void ConnectTo(Node* other, float cost);
    };

    class NodeMap
    {
    private:

        int m_width, m_height;
        float m_cellSize;

        Node** m_nodes;

    public:

        ~NodeMap()
        {
            if (m_nodes) delete[] m_nodes;
        }

        Node* GetRandomNode();

        Node* GetNearbyNode(Node* target);

        Node* GetStartNode();

        static std::vector<Node*> AStarSearch(Node* startNode, Node* endNode);

        void Initialise(std::vector<std::string> asciiMap, int cellSize);

        Node* GetNode(int x, int y) { return m_nodes[x + m_width * y]; }

        void Draw();

        Node* GetClosestNode(glm::vec2 worldPos);

        float GetCellSize();

    };
}


