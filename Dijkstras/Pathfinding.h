#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>

namespace AIForGames
{

    struct Node;

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

        glm::vec2 position;
        std::vector<Edge> connections;

        float gScore;
        float hScore;
        float fScore;
        Node* previous = nullptr;

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

        static std::vector<Node*> AStarSearch(Node* startNode, Node* endNode);

        static std::vector<Node*> DijkstrasSearch(Node* startNode, Node* endNode);

        void Initialise(std::vector<std::string> asciiMap, int cellSize);

        Node* GetNode(int x, int y) { return m_nodes[x + m_width * y]; }

        void Draw();

        Node* GetClosestNode(glm::vec2 worldPos);

        float GetCellSize();

    };
}


