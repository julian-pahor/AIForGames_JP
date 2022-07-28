#include <raylib.h>
#include <glm/glm.hpp>

#include "Pathfinding.h"
#include "PathAgent.h"
#include "Agent.h"
#include "GoToBehaviour.h"
#include "WanderBehaviour.h"
#include "HuntBehaviour.h"
#include "InvestigateBehaviour.h"
#include "PlayerBehaviour.h"
#include "FSM.h"
#include "Condition.h"
#include "State.h"
#include "DistanceCondition.h"
#include "TimerCondition.h"
#include "InputCondition.h"

#include <vector>
#include <string>
#include <list>
#include <iostream>

using namespace std;
using namespace Precon;

int main()
{
    NodeMap nodeMap;

    list<Agent*> agentList;

    vector<string> asciiMap;
    asciiMap.push_back("0000000000000000000000000000000000");
    asciiMap.push_back("0000000000000000000000000000003300");
    asciiMap.push_back("0011111111111111111111111111111100");
    asciiMap.push_back("0011111111111111111111111111111100");
    asciiMap.push_back("0011111111111111111111111111111100");
    asciiMap.push_back("0011111111111111111111111111111100");
    asciiMap.push_back("0011111111111111111111111111111100");
    asciiMap.push_back("0011111111111111111111111111111100");
    asciiMap.push_back("0011111111111111111111111111111100");
    asciiMap.push_back("0011111111111111111111111111111100");
    asciiMap.push_back("0011111111111111111111111111111100");
    asciiMap.push_back("0011111111111111111111111111111100");
    asciiMap.push_back("0011111111111111111111111111111100");
    asciiMap.push_back("0022000000000000000000000000000000");
    asciiMap.push_back("0000000000000000000000000000000000");

    nodeMap.Initialise(asciiMap, 25);

    DistanceCondition* closerThan5 = new DistanceCondition(5.0f, true);
    DistanceCondition* furtherThan5 = new DistanceCondition(5.0f, false);
    TimerCondition* countdown4 = new TimerCondition(4.0f);
    TimerCondition* countdown5 = new TimerCondition(5.0f);
    InputCondition* spacebarPress = new InputCondition(KEY_SPACE);

    //register these states with the FSM, so it's responsible for deleting them now
    State* wanderState = new State(new WanderBehaviour());
    State* huntState = new State(new HuntBehaviour());
    State* investigateState = new State(new InvestigateBehaviour());
    State* gotoState = new State(new GoToBehaviour());

    gotoState->AddTransition(countdown5, investigateState);
    gotoState->AddTransition(closerThan5, huntState);

    wanderState->AddTransition(closerThan5, huntState);
    wanderState->AddTransition(spacebarPress, gotoState);

    huntState->AddTransition(furtherThan5, investigateState);

    investigateState->AddTransition(countdown4, wanderState);
    investigateState->AddTransition(closerThan5, huntState);
    investigateState->AddTransition(spacebarPress, gotoState);

    //make a FSM that starts off wandering
    FSM* fsm = new FSM(wanderState);
    fsm->AddState(wanderState);
    fsm->AddState(huntState);
    fsm->AddState(investigateState);

    Agent agent(&nodeMap, new PlayerBehaviour());
    agent.SetNode(nodeMap.GetStartNode());
    agent.SetColor(GOLD);
    agent.SetSpeed(6);

    Agent agent2(&nodeMap, fsm);
    agent2.SetNode(nodeMap.GetRandomNode());
    agent2.SetSpeed(3);
    agent2.SetTarget(&agent);

    agentList.push_back(&agent);
    agentList.push_back(&agent2);

    InitWindow(1000, 600, "Precon The ManBat!");

    Color screenShade = BLACK;
    float shadeCD{};
    float shadeTimer = .02f;
    screenShade.a = 0;

    while (!WindowShouldClose())
    {

        shadeCD += GetFrameTime();

        if (screenShade.a < BLACK.a && shadeCD > shadeTimer)
        {
            screenShade.a += 1; 
            shadeCD = 0;
        }
        
        if (IsKeyPressed(KEY_SPACE))
        {
            screenShade.a = 35;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        nodeMap.Draw();

        for (Agent* a : agentList)
        {
            a->Update(GetFrameTime());
            a->Draw();
        }

        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), screenShade);

        if (agent.CheckWin())
        {
            agentList.clear();
            screenShade = BLUE;
            screenShade.a = 175;
            DrawText("Precon has Escaped...", ((GetScreenWidth() / 2) - 250), GetScreenHeight() / 2, 50, BLACK);
        }

        if (agent2.CheckKill())
        {
            agentList.clear();
            screenShade = RED;
            screenShade.a = 175;
            DrawText("Precon has fallen...", ((GetScreenWidth() / 2) - 250), GetScreenHeight() / 2, 50, BLACK);
        }
        DrawFPS(15, 15);

        EndDrawing();
    }

    CloseWindow();
    
}

