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

    //asciiMap used to draw the nodeMap used for path finding;
    // 0 = boundary
    // 1 = movable space
    // 2 = entry point for player (spawn point)
    // 3 = exit point for player (goal)
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

    //Creating conditions to use for state transitions within the Finite State Machine (fsm)
    DistanceCondition* closerThan5 = new DistanceCondition(5.0f, true);
    DistanceCondition* furtherThan5 = new DistanceCondition(5.0f, false);
    TimerCondition* countdown4 = new TimerCondition(4.0f);
    TimerCondition* countdown5 = new TimerCondition(5.0f);
    InputCondition* spacebarPress = new InputCondition(KEY_SPACE);

    //Registering the behaviours as states and adding the needed transitions for each state
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

    //make a FSM that starts off wandering and pass through the created states
    FSM* fsm = new FSM(wanderState);
    fsm->AddState(wanderState);
    fsm->AddState(huntState);
    fsm->AddState(investigateState);

    //Initialisation of a 'player' type agent
    Agent agent(&nodeMap, new PlayerBehaviour());
    agent.SetNode(nodeMap.GetStartNode());
    agent.SetColor(GOLD);
    agent.SetSpeed(6);

    //Initialisation of an agent which makes use of the FSM
    Agent agent2(&nodeMap, fsm);
    agent2.SetNode(nodeMap.GetRandomNode());
    agent2.SetSpeed(3);
    agent2.SetTarget(&agent);

    //Agents are pushed into a list used to update and draw them
    agentList.push_back(&agent);
    agentList.push_back(&agent2);

    InitWindow(1000, 600, "Precon The ManBat!");

    //screenShade is the COLOR variable used to darken the screen over time;
    Color screenShade = BLACK;
    //It executes a progressive addition to it's alpha value using a cooldown system with 2 floats
    float shadeCD{};
    float shadeTimer = .01f;
    screenShade.a = 0;

    while (!WindowShouldClose())
    {
        shadeCD += GetFrameTime();

        //Once the cooldown is higher than the timer it adds to the alpha value;
        if (screenShade.a < BLACK.a && shadeCD > shadeTimer)
        {
            screenShade.a += 1; 
            shadeCD = 0;
        }
        
        //
        if (IsKeyPressed(KEY_SPACE))
        {
            screenShade.a = 25;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        nodeMap.Draw();

        //Agents from the list are updated
        for (Agent* a : agentList)
        {
            a->Update(GetFrameTime());
            a->Draw();
        }

        //Progressive black tint is drawn over the entire screen
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), screenShade);

        //If win condition is met it clears list and displays a victory screen for that level
        if (agent.CheckWin())
        {
            agentList.clear();
            screenShade = BLUE;
            screenShade.a = 175;
            DrawText("Precon has Escaped...", ((GetScreenWidth() / 2) - 250), GetScreenHeight() / 2, 50, BLACK);
        }

        //If the player is caught/killed it displays a lost screen for that level
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

