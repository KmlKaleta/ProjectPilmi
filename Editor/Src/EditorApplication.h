//
// Created by Kamil on 16.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_EDITOR_APPLICATION_H
#define SHEEP_GOES_DEVILE_EDITOR_APPLICATION_H

#include "AssetManager.h"
#include "EditorHierarchy.h"
#include "EditorLevel.h"
#include "EntitySelection.h"
#include "EditorUndoRedo.hpp"

struct UndoRedoContext;

struct EditorApplication
{
    EntitySelection Selection;
    EditorHierarchy Hierarchy;
    EditorLevel Level;
    AssetManager Assets;
    EditorUndoRedo UndoRedo;

    bool Init();

    bool Update(UndoRedoContext& ctx);

    void Close();
};
#endif //SHEEP_GOES_DEVILE_EDITOR_APPLICATION_H
