//
// Created by Kamil on 15.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_EDITOR_APPLICATION_UI_H
#define SHEEP_GOES_DEVILE_EDITOR_APPLICATION_UI_H
#include "EditorComponentsUI.h"
#include "EditorHierarchyUI.h"
#include "EditorLevelUI.h"

struct EditorApplicationUI
{
    EditorLevelUI SceneUI;
    EditorHierarchyUI HierarchyUI;
    EditorComponentsUI ComponentsUI;

    void Init() const;

    void Draw();
};

#endif //SHEEP_GOES_DEVILE_EDITOR_APPLICATION_UI_H
