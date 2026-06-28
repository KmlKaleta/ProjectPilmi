//
// Created by Kamil on 24.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_SPRITE_EDITOR_WINDOW_H
#define SHEEP_GOES_DEVILE_SPRITE_EDITOR_WINDOW_H
#include "SpriteEditor.h"
#include "SpritesExplorer.h"

#include "UI/SpriteEditorUI.h"
#include "UI/SpritesExplorerUI.h"

struct SpriteEditorWindow
{
    SpritesExplorer Explorer;
    SpritesExplorerUI ExplorerUI;

    SpriteEditor Editor;
    SpriteEditorUI EditorUI;

    void Init();

    void Update();
};

#endif //SHEEP_GOES_DEVILE_SPRITE_EDITOR_WINDOW_H
