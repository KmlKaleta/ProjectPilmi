#ifndef SHEEP_GOES_DEVILE_EDITOR_SCENE_H
#define SHEEP_GOES_DEVILE_EDITOR_SCENE_H

#include "raylib.h"
#include "../Renderer.h"
#include "EditorPalette.h"
#include "EditorComponents.h"
#include <vector>

#include "EditorRenderers.h"


struct AssetManager;

struct EditorScene
{
    Camera2D Camera = {};
    int State = 0;
    bool CanInteract = true;
    EditorPalette Palette;
    EditorRenderers RenderersEditor;
    EditorComponents Components;
    size_t CurrentLevel = 0;

    void Init();

    void Update(AssetManager& assetManager);

    void Reset();

    enum
    {
        EDITOR_PALETTE = 0,
        EDITOR_RENDERERS,
        EDITOR_COMPONENTS
    };
};


#endif //SHEEP_GOES_DEVILE_EDITOR_SCENE_H
