#include <raylib.h>
#include <glm/glm.hpp>

#include <vector>
#include <string>
#include <list>
#include <iostream>

int main()
{
    InitWindow(1500, 600, "Precon The ManBat!");

    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(BLACK);

        DrawFPS(15, 15);

        EndDrawing();
    }

    CloseWindow();
    
}

