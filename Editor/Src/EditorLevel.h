//
// Created by Kamil on 15.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_EDITOR_SCENE_H
#define SHEEP_GOES_DEVILE_EDITOR_SCENE_H
#include "EntitySelection.h"
#include "raylib.h"
#include "Systems/EditorSystems.h"

struct AssetManager;

struct EditorLevel
{
    Camera2D Camera{};
    EditorSystems Systems;

    void Init();

    void Update(AssetManager& assetManager, const EntitySelection& selection);
};

#endif //SHEEP_GOES_DEVILE_EDITOR_SCENE_H
