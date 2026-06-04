//
// Created by Kamil on 02.06.2026.
//
#include "EditorUI.h"
#include "SpriteManager.h"
#include "EditorScene.h"
#include <style_dark.h>

#include "raygui.h"

void EditorUi::Init() const
{
    GuiLoadStyleDark();
}

void EditorUi::DrawTexture(const SpriteData& spriteData, const int TexX, const int TexY, const Rectangle rect,
                           const Color color) const
{
    float widthRatio = 1;
    float heightRatio = 1;
    const float spriteWidth = static_cast<float>(spriteData.Tex.width) / static_cast<float>(spriteData.RowCountMax);
    const float spriteHeight = static_cast<float>(spriteData.Tex.height) / static_cast<float>(spriteData.RowCounts.
                                   size());

    if (spriteHeight > spriteWidth)
    {
        widthRatio = spriteWidth / spriteHeight;
    } else
    {
        heightRatio = spriteHeight / spriteWidth;
    }
    constexpr float scale = 0.9f;
    DrawTexturePro(spriteData.Tex, {
                       static_cast<float>(TexX) * spriteWidth,
                       static_cast<float>(TexY) * spriteHeight, spriteWidth, spriteHeight
                   },
                   {
                       rect.x, rect.y,
                       rect.width * widthRatio * scale, rect.height * heightRatio * scale
                   }, {-rect.width * (1 - widthRatio * scale) / 2, -rect.height * (1 - heightRatio * scale) / 2},
                   0, color);
}

void EditorUi::DrawPalette(const SpriteManager& sprites, const float contentX, const float contentY,
                           const float padding, const float cellSpace, const float iconSize, const int iconsInRow,
                           EditorPalette& palette) const
{
    int x = 0;
    int y = 0;

    const int defaultNormal = GuiGetStyle(BUTTON, BASE_COLOR_NORMAL);
    const int defaultHover = GuiGetStyle(BUTTON, BASE_COLOR_FOCUSED);
    const int defaultPressed = GuiGetStyle(BUTTON, BASE_COLOR_PRESSED);

    for (const auto& [id, index] : sprites.Ids)
    {
        const Rectangle rect = {
            contentX + padding + static_cast<float>(x) * cellSpace,
            contentY + padding + static_cast<float>(y) * cellSpace,
            iconSize, iconSize
        };

        const bool isSpriteSelected = palette.AnySelected && palette.SelectedSprite == id;
        if (isSpriteSelected)
        {
            // Normal state
            GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt({100, 200, 100, 255}));

            // Hover
            GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, ColorToInt({80, 160, 80, 255}));

            // Pressed
            GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, ColorToInt({60, 120, 60, 255}));
        }

        if (!GuiButton(rect, ""))
        {
            goto EndIteration;
        }

        if (isSpriteSelected)
        {
            palette.SelectedSprite = 0;
            palette.AnySelected = false;
        } else
        {
            palette.SelectedSprite = id;
            palette.AnySelected = true;
        }

    EndIteration:
        DrawTexture(sprites.Sprites[index], 0, 0, rect, WHITE);

        // Normal state
        GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, defaultNormal);

        // Hover
        GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, defaultHover);

        // Pressed
        GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, defaultPressed);

        if (++x == iconsInRow)
        {
            x = 0;
            y++;
        }
    }
}

float RendererEditorHeight(const EditorScene& editor)
{
    if (!editor.RenderersEditor.AnySelected)
    {
        return 30 * 1;
    }

    return 30 * 4;
}

void FloatSlider(Rectangle rect, float& value, const float min, const float max, float padding = 5)
{
    if (GuiButton({rect.x, rect.y, 20, rect.height}, "#118#"))
    {
        value -= 0.01f;
    }

    rect.x += 25;
    const float sliderWidth = rect.width - padding - 50;
    GuiSlider({rect.x, rect.y, sliderWidth, rect.height}, "", "", &value, min, max);
    rect.x += sliderWidth + padding;

    if (GuiButton({rect.x, rect.y, 20, rect.height}, "#119#"))
    {
        value += 0.01f;
    }
}

void EditorUi::DrawRendererEditor(EditorScene& editor, float contentX, float contentY, const float width,
                                  const float padding) const
{
    contentX += padding;
    contentY += padding;

    if (!editor.RenderersEditor.AnySelected)
    {
        GuiLabel({contentX, contentY, width - padding, 20}, "No Renderer Selected");
        return;
    }

    Renderer& renderer = editor.Renderers[editor.RenderersEditor.SelectedRenderer];

    GuiLabel({contentX, contentY, width - padding, 20},
             TextFormat("Position: ({%.2f}, {%.2f})", renderer.Position.x, renderer.Position.y));

    contentY += 25;

    GuiLabel({contentX, contentY, width - padding, 20}, TextFormat("Scale: {%.2f}", renderer.LocalScale));

    contentY += 25;

    FloatSlider({contentX, contentY, width, 20}, renderer.LocalScale, 0.1f, 5.0f, padding);

    contentY += 25;

    const auto textWidth = static_cast<float>(MeasureText("Layer Order:", 18));
    GuiLabel({contentX, contentY, textWidth - padding, 20},
             TextFormat("Layer Order: {%d}", editor.RenderersEditor.SelectedRenderer));
    if (GuiButton({contentX + textWidth, contentY, 20, 20}, "#118#") && editor.RenderersEditor.SelectedRenderer >= 1)
    {
        std::swap(editor.Renderers[editor.RenderersEditor.SelectedRenderer],
                  editor.Renderers[editor.RenderersEditor.SelectedRenderer - 1]);
        editor.RenderersEditor.SelectedRenderer--;
    }

    if (GuiButton({contentX + textWidth + 25, contentY, 20, 20}, "#119#") && editor.RenderersEditor.SelectedRenderer <
        editor.Renderers.size() - 1)
    {
        std::swap(editor.Renderers[editor.RenderersEditor.SelectedRenderer],
                  editor.Renderers[editor.RenderersEditor.SelectedRenderer + 1]);
        editor.RenderersEditor.SelectedRenderer++;
    }

    // int index = static_cast<int>(editor.RenderersEditor.SelectedRenderer);
    // int lastIndex = index;
    // GuiValueBox({contentX, contentY, width - padding, 20}, "Layer Order:", &index, 0,
    //             static_cast<int>(editor.Renderers.size()) - 1, true);
    // index = std::clamp(index, 0, static_cast<int>(editor.Renderers.size()) - 1);
    // if (index != lastIndex)
    // {
    //     std::swap(editor.Renderers[index], editor.Renderers[lastIndex]);
    //     editor.RenderersEditor.SelectedRenderer = index;
    // }
}

float PaletteHeight(const float iconsInRow, const float padding, const float cellSpace, const SpriteManager& sprites)
{
    return std::ceil(static_cast<float>(sprites.Sprites.size()) / iconsInRow) * cellSpace +
           padding;
}

void EditorUi::BeforeEditor(EditorScene& editor, const SpriteManager& sprites)
{
    constexpr float sliderWidth = 10;
    constexpr int iconsInRow = 3;
    constexpr float padding = 5;

    Window.Update();

    editor.CanInteract = !CheckCollisionPointRec(GetMousePosition(), {
                                                     Window.Position.x, Window.Position.y,
                                                     Window.Size.x, Window.Size.y
                                                 });

    const float width = Window.Size.x - padding - sliderWidth;
    const float cellSpace = width / iconsInRow;
    const float iconSize = cellSpace - padding;

    float contentHeight = 30;
    switch (editor.State)
    {
        case EditorScene::EDITOR_PALETTE:
            contentHeight += PaletteHeight(iconsInRow, padding, cellSpace, sprites);
            break;
        case EditorScene::EDITOR_RENDERERS:
            contentHeight += RendererEditorHeight(editor);
            break;
        default: break;
    }


    auto [contentX, contentY] = Window.ContentStart();

    Rectangle contentRect = {contentX, contentY, Window.Size.x - padding * 2, contentHeight};
    if (Window.StartDrawing("Editor Window", contentRect))
    {
        GuiComboBox({contentX + padding, contentY + padding, width - padding, 20}, "Sprite Palette;Entity Editor",
                    &editor.State);
        contentY += 25;

        switch (editor.State)
        {
            case EditorScene::EDITOR_PALETTE:
                DrawPalette(sprites, contentX, contentY, padding, cellSpace, iconSize, iconsInRow, editor.Palette);
                break;
            case EditorScene::EDITOR_RENDERERS:
                DrawRendererEditor(editor, contentX, contentY, width, padding);
                break;
            default: break;
        }
    }

    Window.EndDrawing();

    auto [x, y] = editor.RenderersEditor.SelectionClickPosition;
    y += 1;
    if (editor.RenderersEditor.RendererSelection && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !CheckCollisionPointRec(
            GetMousePosition(), {x, y, 100, static_cast<float>(editor.RenderersEditor.RenderersToSelect.size()) * 20}))
    {
        editor.RenderersEditor.RendererSelection = false;
    }

    if (editor.RenderersEditor.RendererSelection)
    {
        for (const auto& renderer : editor.RenderersEditor.RenderersToSelect)
        {
            if (GuiButton({x, y, 100, 20},
                          sprites.Metadata[sprites.Ids.at(editor.Renderers[renderer].Sprite)].Name.c_str()))
            {
                editor.RenderersEditor.SelectedRenderer = renderer;
                editor.RenderersEditor.AnySelected = true;
                editor.RenderersEditor.RendererSelection = false;
            }
            y += 20;
        }
    }
}
