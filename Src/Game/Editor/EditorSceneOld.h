#ifndef SHEEP_GOES_DEVILE_EDITOR_SCENE_OLD_H
#define SHEEP_GOES_DEVILE_EDITOR_SCENE_OLD_H

#include "raylib.h"
#include "../../../Engine/Src/Renderer.h"
#include "EditorPalette.h"
#include "EditorComponents.h"
#include <vector>

#include "EditorStates.h"
#include "EditorRenderers.h"


struct AssetManager;

struct EditorSceneOld
{
    Camera2D Camera = {};
    int State = 0;
    bool CanInteract = true;
    EditorPalette Palette;
    EditorRenderers RenderersEditor;
    EditorComponents Components;
    EditorStates States;
    size_t CurrentLevel = 0;

    void Init();

    void Update(AssetManager& assetManager);

    void Reset();

    enum
    {
        EDITOR_PALETTE = 0,
        EDITOR_RENDERERS,
        EDITOR_COMPONENTS,
        EDITOR_ACTIONS,

        EDITOR_COUNT
    };
};


#endif //SHEEP_GOES_DEVILE_EDITOR_SCENE_H
