#include "raylib.h"
#include "Pathfinding.h"
#include "PathAgent.h"
#include "Agent.h"
#include "GoToPoint.h"

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


int main(void)
{
    NodeMap nodeMap;
    

    std::vector<std::string> asciiMap;

    asciiMap.push_back("0000000000000000000000");
    asciiMap.push_back("0101111101111011011100");
    asciiMap.push_back("010111111111111111110");
    asciiMap.push_back("0101000000100001000000");
    asciiMap.push_back("0101111111111111011110");
    asciiMap.push_back("0100000000000000100000");
    asciiMap.push_back("0111111111111111111110");
    asciiMap.push_back("0101111111111111111110");
    asciiMap.push_back("0100000000000000001000");
    asciiMap.push_back("0111111111111111111110");
    asciiMap.push_back("0101111111111111111110");
    asciiMap.push_back("0100000000000000001000");
    asciiMap.push_back("0111111111111111111110");
    asciiMap.push_back("0000000000000000000000");

    nodeMap.Initialise(asciiMap, 30);
    
    Agent agent(&nodeMap, new GoToPoint());
    

    Node* start = nodeMap.GetNode(1, 2);
    Node* end = nodeMap.GetNode(16, 5);

    std::vector<Node*> nodeMapPath = nodeMap.DijkstrasSearch(start, end);

    Color lineColor = { 255, 255, 255, 255 };

    

    InitWindow(850, 450, "raylib [core] example - basic window");

    

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        
        nodeMap.Draw();
        DrawPath(nodeMapPath, RED);
        DrawText("Green = Start", 675, 20, 16, WHITE);
        DrawText("Purple = End", 675, 40, 16, WHITE);
        DrawText("LeftClick = SetStart", 675, 60, 15, WHITE);
        DrawText("RightClick = SetEnd", 675, 80, 15, WHITE);

        agent.Update(GetFrameTime());
        agent.Draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}