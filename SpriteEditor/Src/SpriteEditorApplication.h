//
// Created by Kamil on 26.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_SPRITE_EDITOR_APPLICATION_H
#define SHEEP_GOES_DEVILE_SPRITE_EDITOR_APPLICATION_H
#include "SpriteEditorScene.h"
#include "SpriteEditorWindow.h"
#include "UI/CameraControlUI.h"

struct SpriteEditorApplication
{
    SpriteEditorWindow Window{};
    SpriteEditorScene Scene{};
    CameraControlUI CameraUI;

    bool Init();

    bool Update();

    void Close();
};

#endif //SHEEP_GOES_DEVILE_SPRITE_EDITOR_APPLICATION_H
