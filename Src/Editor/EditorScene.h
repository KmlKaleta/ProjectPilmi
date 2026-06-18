//
// Created by Kamil on 15.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_EDITOR_SCENE_H
#define SHEEP_GOES_DEVILE_EDITOR_SCENE_H
#include "EntityStorage.h"
#include "raylib.h"
#include "UI/EditorApplicationUI.h"

struct EditorScene
{
    RenderTexture2D SceneTexture;
    EntityStorage Entities;
    EditorApplicationUI Hierarchy;

    void Update();
};

#endif //SHEEP_GOES_DEVILE_EDITOR_SCENE_H
