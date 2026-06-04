#ifndef SHEEP_GOES_DEVILE_EDITOR_SCENE_H
#define SHEEP_GOES_DEVILE_EDITOR_SCENE_H

#include "raylib.h"
#include "Renderer.h"
#include "EditorPalette.h"
#include <vector>

#include "EditorRenderers.h"


struct AssetManager;

struct EditorScene
{
    Camera2D Camera = {};
    int State = 0;
    bool CanInteract = true;
    std::vector<Renderer> Renderers;
    EditorPalette Palette;
    EditorRenderers RenderersEditor;

    void Init(const AssetManager& assetManager);

    void Update(const AssetManager& assetManager);

    void Reset(const AssetManager& assetManager);

    enum
    {
        EDITOR_PALETTE = 0,
        EDITOR_RENDERERS
    };
};


#endif //SHEEP_GOES_DEVILE_EDITOR_SCENE_H
