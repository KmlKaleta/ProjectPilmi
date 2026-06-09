#include <raylib.h>
#include <rlImGui.h>
#include <imgui.h>
#include <Gameplay.h>

int main()
{
#if PRODUCTION_BUILD == 1
    SetTraceLogLevel(LOG_NONE);
#endif // PRODUCTION_BUILD == 1

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN);

    InitWindow(1900, 900, "Sheep Goes Devile");
    SetExitKey(KEY_NULL);
    SetTargetFPS(240);

    rlImGuiSetup(true);

    ImGuiIO &io = ImGui::GetIO();
    io.FontGlobalScale = 2;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    Gameplay gameplay;
    AssetManager assetManager;
    EditorScene editorScene;
    assetManager.LoadAll(editorScene);

    GameplayUpdateArgs updateArgs;
    updateArgs.AssetManager = assetManager;
    updateArgs.EditorScene = editorScene;

    if (!gameplay.Init(updateArgs))
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
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport()->ID);
        ImGui::PopStyleColor(2);

        if (!gameplay.Update(updateArgs))
        {
            CloseWindow();
        }

        rlImGuiEnd();
        EndDrawing();
    }

    rlImGuiShutdown();
    CloseWindow();
    gameplay.Close(updateArgs);

    return 0;
}