#include "ImGuiManager.h"
#include <imgui.h>

#include "EditorSceneOld.h"

void ImGuiManager::AfterGame(EditorSceneOld &editor, AssetManager &assetManager)
{
    if (IsKeyPressed(KEY_F10))
    {
        Enable = !Enable;
    }

    if (!Enable)
    {
        return;
    }

    ImGui::Begin("Game Control");

    ImGui::InputFloat("Zoom:", &Zoom, 0.1, 1, "%.2f");
    if (Zoom <= 0)
    {
        Zoom = 0.01f;
    }

    editor.Camera.zoom = Zoom;
    SpriteEditor.Camera.zoom = Zoom;

    ImGui::End();

    ImGui::Begin("Editor");

    const char *panels[PANEL_COUNT] = {"Sprite Editor"};
    ImGui::Combo("Panel:", &ActivePanel, panels, PANEL_COUNT);

    switch (ActivePanel)
    {
        case PANEL_SPRITE_EDITOR:
            SpriteEditor.AfterGame(editor, assetManager);
            break;
        default:
            break;
    }

    ImGui::End();
}

void ImGuiManager::Init(const AssetManager& assetManager)
{
}
