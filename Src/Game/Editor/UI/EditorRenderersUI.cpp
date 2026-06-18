//
// Created by Kamil on 04.06.2026.
//
#include "EditorRenderersUI.h"
#include "Editor/EditorSceneOld.h"
#include <raygui.h>

#include "LevelManager.h"
#include "Range.hpp"

float EditorRenderersUI::GetHeight(const EditorSceneOld& editor, const float padding) const
{
    if (!editor.RenderersEditor.AnySelected)
    {
        return (20 + padding) * 1;
    }

    return (20 + padding) * 8;
}

void EditorRenderersUI::Draw(const float width, const float contentX, float contentY, const float padding,
                             EditorSceneOld& editor, LevelData& levelData, const SpriteManager& sprites) const
{
    if (!editor.RenderersEditor.AnySelected)
    {
        GuiLabel({contentX, contentY, width - padding, 20}, "No Renderer Selected");
        return;
    }

    Renderer& renderer = levelData.GetRenderer(editor.RenderersEditor.GetSelectedRenderer());

    GuiLabel({contentX, contentY, width - padding, 20},
             TextFormat("Position: ({%.2f}, {%.2f})", renderer.Position.x, renderer.Position.y));

    contentY += 20 + padding;

    GuiLabel({contentX, contentY, width - padding, 20}, TextFormat("Scale: {%.2f}", renderer.LocalScale));

    contentY += 20 + padding;

    FloatSlider({contentX, contentY, width, 20}, renderer.LocalScale, 0.1f, 5.0f, padding);

    contentY += 20 + padding;

    const auto textWidth = static_cast<float>(MeasureText("Layer Order:", 18));
    GuiLabel({contentX, contentY, textWidth - padding, 20},
             TextFormat("Layer Order: {%d}", editor.RenderersEditor.GetSelectedRenderer()));
    if (GuiButton({contentX + textWidth, contentY, 20, 20}, "#118#") && editor.RenderersEditor.GetSelectedRenderer() >=
        1)
    {
        levelData.SwapEntities(editor.RenderersEditor.GetSelectedRenderer(),
                               editor.RenderersEditor.GetSelectedRenderer() - 1);
        editor.RenderersEditor.SelectRenderer(editor.RenderersEditor.GetSelectedRenderer() - 1);
    }

    if (GuiButton({contentX + textWidth + 25, contentY, 20, 20}, "#119#") && editor.RenderersEditor.
        GetSelectedRenderer() <
        levelData.size() - 1)
    {
        levelData.SwapEntities(editor.RenderersEditor.GetSelectedRenderer(),
                               editor.RenderersEditor.GetSelectedRenderer() + 1);
        editor.RenderersEditor.SelectRenderer(editor.RenderersEditor.GetSelectedRenderer() + 1);
    }

    contentY += 20 + padding;

    IntField({contentX, contentY, width - padding, 20}, renderer.TexX, "Tex X:", padding);

    contentY += 20 + padding;

    IntField({contentX, contentY, width - padding, 20}, renderer.TexY, "Tex Y:", padding);
    renderer.ClampTex(sprites);

    contentY += 20 + padding;

    if (GuiButton({contentX, contentY, width - padding, 20}, "Copy"))
    {
    }

    contentY += 20 + padding;

    if (GuiButton({contentX, contentY, width - padding, 20}, "Paste"))
    {
    }
}
