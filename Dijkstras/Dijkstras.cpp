#include "raylib.h"
#include "Pathfinding.h"
#include "PathAgent.h"
#include "GotoPointBehaviour.h"
#include "Agent.h"
#include "WanderBehaviour.h"
#include "FollowBehaviour.h"

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
    asciiMap.push_back("0000000000000000000000000000");
    asciiMap.push_back("0101110111011101110111011100");
    asciiMap.push_back("0101011101110111011101110110");
    asciiMap.push_back("0101000100010001000100000000");
    asciiMap.push_back("0101000100010001000100000000");
    asciiMap.push_back("0101111111111111111111111110");
    asciiMap.push_back("0101111111111111111111111110");
    asciiMap.push_back("0100000000000000000000001000");
    asciiMap.push_back("0111111111111111111111111110");
    asciiMap.push_back("0101000100010001000100000000");
    asciiMap.push_back("0101111111111111111111111110");
    asciiMap.push_back("0101000100010001000100000000");
    asciiMap.push_back("0111111111111111111111111110");
    asciiMap.push_back("0101000100010001000100000000");
    asciiMap.push_back("0101111111111111111111111110");
    asciiMap.push_back("0100000000000000000000001000");
    asciiMap.push_back("0111111111111111111111111110");
    asciiMap.push_back("0000000000000000000000000000");

    nodeMap.Initialise(asciiMap, 30);


    Agent agent(&nodeMap, new GotoPointBehaviour());
    agent.SetNode(nodeMap.GetRandomNode());
    agent.SetSpeed(16);

    Agent agent2(&nodeMap, new WanderBehaviour());
    agent2.SetNode(nodeMap.GetRandomNode());
    agent2.SetSpeed(4);

    Agent agent3(&nodeMap, new WanderBehaviour());
    agent3.SetNode(nodeMap.GetRandomNode());
    agent3.SetSpeed(2);

    Agent agent4(&nodeMap, new FollowBehaviour());
    agent4.SetNode(nodeMap.GetRandomNode());
    agent4.SetSpeed(4);
    agent4.SetTarget(&agent);



    InitWindow(1500, 600, "Djikstras!");



    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(BLACK);

        nodeMap.Draw();

        agent.Update(GetFrameTime());
        agent.Draw();

        agent2.Update(GetFrameTime());
        agent2.Draw();

        agent3.Update(GetFrameTime());
        agent3.Draw();

        agent4.Update(GetFrameTime());
        agent4.Draw();

        EndDrawing();
    }

    CloseWindow();
}

