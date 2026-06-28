//
// Created by Kamil on 26.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_SPRITE_EDITOR_SCENE_H
#define SHEEP_GOES_DEVILE_SPRITE_EDITOR_SCENE_H
#include "raylib.h"

struct SpritesExplorer;
struct SpriteEditor;

struct SpriteEditorScene
{
    Camera2D Camera;

    void Init();

    void Update(SpritesExplorer& explorer, const SpriteEditor& editor);
};

#endif //SHEEP_GOES_DEVILE_SPRITE_EDITOR_SCENE_H
