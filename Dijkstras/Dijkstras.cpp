#include "raylib.h"
#include "Pathfinding.h"
#include "PathAgent.h"
#include "GotoPointBehaviour.h"
#include "Agent.h"

#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <iostream>

using namespace AIForGames;



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
    

    
    

    Color lineColor = { 255, 255, 255, 255 };


    InitWindow(850, 450, "raylib [core] example - basic window");



    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(BLACK);

        nodeMap.Draw();

        EndDrawing();
    }

    CloseWindow();
}

