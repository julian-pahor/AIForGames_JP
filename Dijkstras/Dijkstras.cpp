#include "raylib.h"
#include "Pathfinding.h"
#include "PathAgent.h"
#include "GotoPointBehaviour.h"
#include "Agent.h"
#include "WanderBehaviour.h"
#include "FollowBehaviour.h"
#include "SelectorBehaviour.h"
#include "InvestigateBehaviour.h"

#include "FiniteStateMachine.h"
#include "Condition.h"
#include "State.h"
#include "DistanceCondition.h"
#include "TimerCondition.h"

#include "UtilityAI.h"

#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <iostream>
#include <list>

using namespace AIForGames;



int main()
{
    NodeMap nodeMap;

    std::list<Agent*> agentBag;

    std::vector<std::string> asciiMap;
    asciiMap.push_back("00000000000000000000000000000000000000000000");
    asciiMap.push_back("01001111110111011101110111011011110111011100");
    asciiMap.push_back("01011011011101110111011101110110111101110110");
    asciiMap.push_back("01001001000100010001000100010010000100000000");
    asciiMap.push_back("01001001000100010001000100010010000100000000");
    asciiMap.push_back("01011111111111111111111111111111111111111110");
    asciiMap.push_back("01011111111111111111111111111111111111111110");
    asciiMap.push_back("01000000000000000000000000000000000000001000");
    asciiMap.push_back("01111111111111111111111111111111111111111110");
    asciiMap.push_back("01001001000100010001000100010010000100000000");
    asciiMap.push_back("01011111111111111111111111111111111111111110");
    asciiMap.push_back("01001001000100010001000100010010000100000000");
    asciiMap.push_back("01111111111111111111111111111111111111111110");
    asciiMap.push_back("01001001000100010001000100010010000100000000");
    asciiMap.push_back("01011111111111111111111111111111111111111110");
    asciiMap.push_back("01000000000000000000000000000000000000001000");
    asciiMap.push_back("01111111111111111111111111111111111111111110");
    asciiMap.push_back("00000000000000000000000000000000000000000000");

    nodeMap.Initialise(asciiMap, 30);

    //set up a FSM, we're going to have two states with their own conditions
    DistanceCondition* closerThan5 = new DistanceCondition(5.0f, true);
    DistanceCondition* furtherThan5 = new DistanceCondition(5.0f, false);
    TimerCondition* countdown4 = new TimerCondition(4.0f);

    //register these states with the FSM, so it's responsible for deleting them now
    State* wanderState = new State(new WanderBehaviour());
    State* followState = new State(new FollowBehaviour());
    State* investigateState = new State(new InvestigateBehaviour());
    wanderState->AddTransition(closerThan5, followState);
    followState->AddTransition(furtherThan5, investigateState);
    investigateState->AddTransition(countdown4, wanderState);

    //make a FSM that starts off wandering
    FiniteStateMachine* fsm = new FiniteStateMachine(wanderState);
    fsm->AddState(wanderState);
    fsm->AddState(followState);
    fsm->AddState(investigateState);

    Agent agent(&nodeMap, new GotoPointBehaviour());
    agent.SetNode(nodeMap.GetRandomNode());
    agent.SetColor(GOLD);
    agent.SetSpeed(16);

    Agent agent2(&nodeMap, fsm);
    agent2.SetNode(nodeMap.GetRandomNode());
    agent2.SetSpeed(4);
    agent2.SetTarget(&agent);

    UtilityAI* utilityAI = new UtilityAI();
    utilityAI->AddBehaviour(new WanderBehaviour());
    utilityAI->AddBehaviour(new FollowBehaviour());

    Agent agent3(&nodeMap, utilityAI);
    agent3.SetNode(nodeMap.GetRandomNode());
    agent3.SetSpeed(4);
    agent3.SetTarget(&agent);


    
    Agent agent6(&nodeMap, new WanderBehaviour());
    agent6.SetNode(nodeMap.GetRandomNode());
    agent6.SetColor(SKYBLUE);
    agent6.SetSpeed(1);

    Agent agent4(&nodeMap, new WanderBehaviour());
    agent4.SetNode(nodeMap.GetRandomNode());
    agent4.SetColor(SKYBLUE);
    agent4.SetSpeed(1);
    

    Agent agent5(&nodeMap, new WanderBehaviour());
    agent5.SetNode(nodeMap.GetRandomNode());
    agent5.SetSpeed(1);
    agent5.SetColor(SKYBLUE);
    
    
    agentBag.push_back(&agent);
    agentBag.push_back(&agent2);
    agentBag.push_back(&agent3);
    agentBag.push_back(&agent3);
    agentBag.push_back(&agent4);
    agentBag.push_back(&agent5);
    agentBag.push_back(&agent6);

    InitWindow(1500, 600, "Djikstras!");

    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(BLACK);

        nodeMap.Draw();

        for (Agent* a : agentBag)
        {
            a->Update(GetFrameTime());
            a->Draw();
        }

        DrawFPS(15, 15);

        EndDrawing();
    }

    CloseWindow();
}

