//
// Created by Kamil on 04.06.2026.
//
#include "EditorPaletteUI.h"
#include "AssetManagement/SpriteManager.h"
#include <raygui.h>

#include "Editor/EditorPalette.h"

void DrawTexture(const SpriteData& spriteData, const int TexX, const int TexY, const Rectangle rect,
                 const Color color)
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

float PaletteHeight(const float iconsInRow, const float padding, const float cellSpace, const SpriteManager& sprites)
{
    return std::ceil(static_cast<float>(sprites.Data.size()) / iconsInRow) * cellSpace +
           padding;
}

float EditorPaletteUI::CellSpace(const float width) const
{
    return width / static_cast<float>(SpritesInRow);
}

float IconSize(const float cellSpace, const float padding)
{
    return cellSpace - padding;
}

float EditorPaletteUI::GetHeight(const float width, const SpriteManager& sprites, const float padding) const
{
    return PaletteHeight(static_cast<float>(SpritesInRow), padding, CellSpace(width), sprites);
}

void EditorPaletteUI::Draw(const float width, const float contentX, const float contentY, const float padding,
                           EditorPalette& palette, const SpriteManager& sprites) const
{
    int x = 0;
    int y = 0;

    const int defaultNormal = GuiGetStyle(BUTTON, BASE_COLOR_NORMAL);
    const int defaultHover = GuiGetStyle(BUTTON, BASE_COLOR_FOCUSED);
    const int defaultPressed = GuiGetStyle(BUTTON, BASE_COLOR_PRESSED);

    const float cellSpace = CellSpace(width);
    const float iconSize = IconSize(cellSpace, padding);

    for (const auto& [id, index] : sprites.Ids)
    {
        const Rectangle rect = {
            contentX + static_cast<float>(x) * cellSpace + padding,
            contentY + static_cast<float>(y) * cellSpace,
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
        DrawTexture(sprites.Data[index], 0, 0, rect, WHITE);

        // Normal state
        GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, defaultNormal);

        // Hover
        GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, defaultHover);

        // Pressed
        GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, defaultPressed);

        if (++x == SpritesInRow)
        {
            x = 0;
            y++;
        }
    }
}
