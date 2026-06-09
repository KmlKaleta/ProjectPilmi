//
// Created by Kamil on 03.06.2026.
//
#include "EditorPalette.h"
#include "AssetManagement/SpriteManager.h"
#include "LevelManager.h"

void EditorPalette::Update(const Vector2 mousePosition,const bool canInteract, LevelData& level, const SpriteManager& sprites) const
{
    if (!canInteract || !AnySelected)
    {
        return;
    }

    const SpriteData spriteData = sprites.FromId(SelectedSprite);
    spriteData.Render(mousePosition, 0, 0, false, 1.f, {255, 255, 255, 150});
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        level.AddRenderer({SelectedSprite, mousePosition, 1.f, false, 0, 0});
    }
}
