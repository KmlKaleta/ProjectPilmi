//
// Created by Kamil on 03.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_EDITOR_PALETTE_H
#define SHEEP_GOES_DEVILE_EDITOR_PALETTE_H
#include <cstdint>

struct Vector2;
struct LevelData;
struct SpriteManager;

struct EditorPalette
{
    uint64_t SelectedSprite = 0;
    bool AnySelected = false;

    void Update(Vector2 mousePosition, bool canInteract, LevelData& level, const SpriteManager& sprites) const;
};

#endif //SHEEP_GOES_DEVILE_EDITOR_PALETTE_H
