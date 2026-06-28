//
// Created by Kamil on 27.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_SPRITE_EDITOR_UI_H
#define SHEEP_GOES_DEVILE_SPRITE_EDITOR_UI_H
struct SpritesExplorer;
struct SpriteEditor;

struct SpriteEditorUI
{
    void Draw(SpriteEditor& editor, SpritesExplorer& explorer) const;
};
#endif //SHEEP_GOES_DEVILE_SPRITE_EDITOR_UI_H
