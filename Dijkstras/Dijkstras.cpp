#include "raylib.h"
#include "Pathfinding.h"
#include "PathAgent.h"

#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <iostream>

using namespace AIForGames;

void DrawPath(std::vector<Node*> path, Color lineColor)
{
    DrawCircle((path[0]->position.x + 0.5f) * 30,
        (path[0]->position.y + 0.5f) * 30,
        5,
        GREEN);

    for (int i = 0; i < path.size() - 1; i++)
    {
        DrawLine((path[i]->position.x + 0.5f) * 30,
            (path[i]->position.y + 0.5f) * 30,
            (path[i + 1]->position.x + 0.5f) * 30,
            (path[i + 1]->position.y + 0.5f) * 30,
            lineColor);
    }

    DrawCircle((path[path.size() - 1]->position.x + 0.5f) * 30,
        (path[path.size() - 1]->position.y + 0.5f) * 30,
        5,
        DARKPURPLE);
}

int main()
{
    NodeMap nodeMap;

    std::vector<std::string> asciiMap;
    asciiMap.push_back("000000000000");
    asciiMap.push_back("010111011100");
    asciiMap.push_back("010101110110");
    asciiMap.push_back("010100000000");
    asciiMap.push_back("010111111110");
    asciiMap.push_back("010000001000");
    asciiMap.push_back("011111111110");
    asciiMap.push_back("000000000000");

    nodeMap.Initialise(asciiMap, 30);

    Node* start = nodeMap.GetNode(1, 1);
    Node* end = nodeMap.GetNode(10, 2);
    //std::vector<Node*> nodeMapPath = nodeMap.DijkstrasSearch(start, end);

    PathAgent agent;
    agent.SetNode(start);
    agent.SetSpeed(32);

    Color lineColor = { 255, 255, 255, 255 };


    InitWindow(850, 450, "raylib [core] example - basic window");



    while (!WindowShouldClose())
    {

        if (IsMouseButtonPressed(0))
        {
            Vector2 mousePos = GetMousePosition();
            start = nodeMap.GetClosestNode(glm::vec2(mousePos.x, mousePos.y));
            agent.SetNode(start);
        }
        if (IsMouseButtonPressed(1))
        {
            Vector2 mousePos = GetMousePosition();
            end = nodeMap.GetClosestNode(glm::vec2(mousePos.x, mousePos.y));
            agent.GoToNode(end);
        }

        BeginDrawing();
        ClearBackground(BLACK);


        nodeMap.Draw();
        agent.Update(GetFrameTime());
        agent.Draw();
        //DrawPath(nodeMapPath, lineColor);


        EndDrawing();
    }

    CloseWindow();
}

