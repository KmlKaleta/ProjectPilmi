//
// Created by Kamil on 18.06.2026.
//
#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"
#include "EditorWindow.h"
#include "ImGuiExtensions.h"

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

    rlImGuiSetup(true);

    ImGuiIO& io = ImGui::GetIO();
    io.FontGlobalScale = 2;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    EditorWindow editor;

    if (!editor.Init())
    {
        return 0;
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        rlImGuiBegin();

        ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
        ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});
        ImGui::PopStyleColor(2);

        ImGui::DockingSetup();

        if (!editor.Update())
        {
            CloseWindow();
        }

        rlImGuiEnd();
        EndDrawing();
    }

    rlImGuiShutdown();
    CloseWindow();
    editor.Close();

    return 0;
}
