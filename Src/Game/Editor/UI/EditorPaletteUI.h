//
// Created by Kamil on 04.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_EDITOR_PALETTE_UI_H
#define SHEEP_GOES_DEVILE_EDITOR_PALETTE_UI_H
struct SpriteManager;
struct EditorPalette;

struct EditorPaletteUI
{
    int SpritesInRow = 4;

    float CellSpace(float width) const;

    float GetHeight(float width, const SpriteManager& sprites, float padding) const;

    void Draw(float width, float contentX, float contentY, float padding, EditorPalette& palette, const SpriteManager& sprites) const;
private:
};
#endif //SHEEP_GOES_DEVILE_EDITOR_PALETTE_UI_H
