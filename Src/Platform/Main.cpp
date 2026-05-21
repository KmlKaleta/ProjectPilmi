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
	InitWindow(1900, 900, "window name");
	SetExitKey(KEY_NULL);
	SetTargetFPS(240);

	rlImGuiSetup(true);

	ImGuiIO& io = ImGui::GetIO();
	io.FontGlobalScale = 2;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    Gameplay gameplay;
	if (!gameplay.init())
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

		if (!gameplay.update())
		{
			CloseWindow();
		}

		rlImGuiEnd();
		EndDrawing();
	}

	rlImGuiShutdown();
	CloseWindow();
	gameplay.close();

	return 0;
}