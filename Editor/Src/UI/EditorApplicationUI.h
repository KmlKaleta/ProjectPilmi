//
// Created by Kamil on 15.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_EDITOR_APPLICATION_UI_H
#define SHEEP_GOES_DEVILE_EDITOR_APPLICATION_UI_H
#include "EditorComponentsUI.h"
#include "EditorHierarchyUI.h"
#include "EditorLevelUI.h"

struct EditorApplication;

struct EditorApplicationUI
{
    EditorLevelUI SceneUI;
    EditorHierarchyUI HierarchyUI;
    EditorComponentsUI ComponentsUI;

    void Draw(EditorApplication& editor) const;
};

#endif //SHEEP_GOES_DEVILE_EDITOR_APPLICATION_UI_H
