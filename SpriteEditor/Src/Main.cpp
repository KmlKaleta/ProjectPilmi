//
// Created by Kamil on 24.06.2026.
//

#include "imgui.h"
#include "ImGuiExtensions.h"
#include "rlImGui.h"
#include "SpriteEditorApplication.h"

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
    ImFont* font = io.Fonts->AddFontFromFileTTF(RESOURCES_PATH "Pangolin-Regular.ttf");

    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    SpriteEditorApplication editor;

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
        ImGui::PushFont(font);

        ImGui::DockingSetup();

        if (!editor.Update())
        {
            CloseWindow();
        }

        ImGui::PopFont();

        rlImGuiEnd();
        EndDrawing();
    }

    rlImGuiShutdown();
    CloseWindow();
    editor.Close();

    return 0;
}
