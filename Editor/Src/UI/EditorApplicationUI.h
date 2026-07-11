//
// Created by Kamil on 15.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_EDITOR_APPLICATION_UI_H
#define SHEEP_GOES_DEVILE_EDITOR_APPLICATION_UI_H
#include "EditorComponentsUI.h"
#include "EditorHierarchyUI.h"
#include "EditorLevelUI.h"
#include "EditorMenuUI.h"

struct EditorApplication;
struct UndoRedoContext;

struct EditorApplicationUI
{
    EditorLevelUI SceneUI;
    EditorHierarchyUI HierarchyUI;
    EditorComponentsUI ComponentsUI;
    EditorMenuUI MenuUI;

    void Draw(EditorApplication& editor, UndoRedoContext& ctx) const;
};

#endif //SHEEP_GOES_DEVILE_EDITOR_APPLICATION_UI_H
