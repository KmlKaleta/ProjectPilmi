//
// Created by Kamil on 02.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_EDITOR_UI_H
#define SHEEP_GOES_DEVILE_EDITOR_UI_H

#include "RayGui/FloatingWindow.hpp"

struct EditorPalette;
struct SpriteData;
struct SpriteManager;
struct EditorScene;

struct EditorUi
{
    FloatingWindow Window;

    void Init() const;

    void DrawTexture(const SpriteData& spriteData, int TexX, int TexY, Rectangle rect,
                     Color color) const;

    void DrawPalette(const SpriteManager& sprites, float contentX, float contentY, float padding,
                     float cellSpace, float iconSize, int iconsInRow, EditorPalette& palette) const;

    void DrawRendererEditor(EditorScene& editor, float contentX, float contentY, float width, float padding) const;

    void BeforeEditor(EditorScene& editor, const SpriteManager& sprites);
};

#endif //SHEEP_GOES_DEVILE_EDITOR_UI_H
