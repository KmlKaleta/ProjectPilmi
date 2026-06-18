//
// Created by Kamil on 16.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_EDITOR_APPLICATION_H
#define SHEEP_GOES_DEVILE_EDITOR_APPLICATION_H
#include "AssetManager.h"
#include "UI/EditorApplicationUI.h"

struct EditorApplication
{
    AssetManager Assets;

    bool Init();

    bool Update();

    void Close();
};
#endif //SHEEP_GOES_DEVILE_EDITOR_APPLICATION_H
