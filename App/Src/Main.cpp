//
// Created by Kamil on 18.06.2026.
//
#include "GameApplication.h"
#include "raylib.h"

int main()
{
#if PRODUCTION_BUILD == 1
    SetTraceLogLevel(LOG_NONE);
#endif // PRODUCTION_BUILD == 1

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN);

    InitWindow(1900, 900, "Sheep Goes Devile");
    SetWindowMinSize(600, 400);
    SetExitKey(KEY_NULL);
    SetTargetFPS(240);

    GameApplication editor;

    if (!editor.Init())
    {
        return 0;
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);


        if (!editor.Update())
        {
            CloseWindow();
        }

        EndDrawing();
    }

    CloseWindow();
    editor.Close();

    return 0;
}