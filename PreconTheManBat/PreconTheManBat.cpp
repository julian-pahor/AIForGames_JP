#include <raylib.h>
#include <glm/glm.hpp>

#include "Pathfinding.h"
#include "PathAgent.h"

#include <vector>
#include <string>
#include <list>
#include <iostream>

using namespace std;
using namespace Precon;

int main()
{
    NodeMap nodeMap;

    vector<string> asciiMap;
    asciiMap.push_back("00000000000000000000000000000000");
    asciiMap.push_back("00000000000000000000000000000000");
    asciiMap.push_back("00000000000000000000000000000000");
    asciiMap.push_back("00000000000000000000000000000000");
    asciiMap.push_back("00000000001111111111100000000000");
    asciiMap.push_back("00000000001111111111100000000000");
    asciiMap.push_back("00000000001111111111100000000000");
    asciiMap.push_back("00000000001111111111100000000000");
    asciiMap.push_back("00000000001111111111100000000000");
    asciiMap.push_back("00000000000000000000000000000000");
    asciiMap.push_back("00000000000000000000000000000000");
    asciiMap.push_back("00000000000000000000000000000000");
    asciiMap.push_back("00000000000000000000000000000000");

    nodeMap.Initialise(asciiMap, 25);

    InitWindow(1600, 900, "Precon The ManBat!");

    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(BLACK);

        nodeMap.Draw();


        DrawFPS(15, 15);

        EndDrawing();
    }

    CloseWindow();
    
}

