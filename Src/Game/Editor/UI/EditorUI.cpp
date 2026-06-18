//
// Created by Kamil on 02.06.2026.
//
#include "EditorUI.h"
#include "AssetManagement/SpriteManager.h"
#include "../EditorSceneOld.h"
#include <style_dark.h>

#include "AssetManagement/AssetManager.h"
#include "raygui.h"

void EditorUi::Init()
{
    GuiLoadStyleDark();
    Window.Position = {100, 100};
}


void HandleRendererSelection(EditorSceneOld& editor, LevelData& levelData, const SpriteManager& sprites)
{
    auto [x, y] = editor.RenderersEditor.SelectionClickPosition;
    y += 1;
    if (editor.RenderersEditor.GetSelectedRenderer() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
        !CheckCollisionPointRec(GetMousePosition(), {
                                    x, y, 100, static_cast<float>(editor.RenderersEditor.RenderersToSelect.size()) * 20
                                }))
    {
        editor.RenderersEditor.CancelSelection();
        return;
    }

    for (const auto& renderer : editor.RenderersEditor.RenderersToSelect)
    {
        if (GuiButton({x, y, 100, 20}, sprites.Metadata[sprites.Ids.at(levelData.GetRenderer(renderer).Sprite)].
                      Name.c_str()))
        {
            editor.RenderersEditor.SelectRenderer(renderer);
        }
        y += 20;
    }
}

void EditorUi::AfterEditor(EditorSceneOld& editor, AssetManager& assetManager)
{
    editor.CanInteract = !CheckCollisionPointRec(GetMousePosition(), {
                                                     Window.Position.x, Window.Position.y,
                                                     Window.Size.x, Window.Size.y
                                                 }) && !CheckCollisionPointRec(
                             GetMousePosition(), LevelDataUI.GetRect());

    Window.Update();


    LevelDataUI.Draw(editor, assetManager.Levels);
    constexpr float sliderWidth = 10;
    constexpr float padding = 5;
    const float width = Window.Size.x - padding - padding - sliderWidth;
    auto& levelData = assetManager.Levels.Data[editor.CurrentLevel];

    float contentHeight = 30;
    switch (editor.State)
    {
        case EditorSceneOld::EDITOR_PALETTE:
            contentHeight += PaletteUI.GetHeight(width, assetManager.Sprites, padding);
            break;
        case EditorSceneOld::EDITOR_RENDERERS:
            contentHeight += RenderersUI.GetHeight(editor, padding);
            break;
        case EditorSceneOld::EDITOR_COMPONENTS:
            contentHeight += ComponentsUI.GetHeight(editor, padding);
            break;
        case EditorSceneOld::EDITOR_ACTIONS:
            contentHeight += ActionsUI.GetHeight(editor, levelData);
            break;
        default: break;
    }

    auto [contentX, contentY] = Window.ContentStart();

    const Rectangle contentRect = {contentX, contentY, Window.Size.x - padding * 2, contentHeight};
    contentX += padding;
    contentY += padding;

    if (Window.StartDrawing("Editor Window", contentRect))
    {
        GuiComboBox({contentX, contentY, width, 20},
                    "Sprite Palette;Entity Editor;Components Editor;Actions Editor",
                    &editor.State);
        contentY += 20 + padding;
        switch (editor.State)
        {
            case EditorSceneOld::EDITOR_PALETTE:
                PaletteUI.Draw(width, contentX, contentY, padding, editor.Palette, assetManager.Sprites);
                break;
            case EditorSceneOld::EDITOR_RENDERERS:
                RenderersUI.Draw(width, contentX, contentY, padding, editor,
                                 levelData, assetManager.Sprites);
                break;
            case EditorSceneOld::EDITOR_COMPONENTS:
                ComponentsUI.Draw(width, contentX, contentY, padding, editor,
                                  levelData);
                break;
            case EditorSceneOld::EDITOR_ACTIONS:
                ActionsUI.Draw(contentX, contentY, width, padding, editor, levelData);
                break;
            default: break;
        }
    }

    Window.EndDrawing();

    if (!editor.RenderersEditor.IsSelectionPhase())
    {
        return;
    }

    if (editor.State == EditorSceneOld::EDITOR_RENDERERS || editor.State == EditorSceneOld::EDITOR_COMPONENTS)
    {
        HandleRendererSelection(editor, levelData, assetManager.Sprites);
    } else
    {
        editor.RenderersEditor.CancelSelection();
    }
}
