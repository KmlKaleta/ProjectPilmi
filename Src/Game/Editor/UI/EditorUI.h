//
// Created by Kamil on 02.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_EDITOR_UI_H
#define SHEEP_GOES_DEVILE_EDITOR_UI_H

#include "EditorStatesUI.h"
#include "EditorComponentsUI.h"
#include "EditorPaletteUI.h"
#include "EditorRenderersUI.h"
#include "LevelDataUI.h"
#include "../../RayGui/FloatingWindow.hpp"

struct AssetManager;

struct EditorUi
{
    FloatingWindow Window;

    EditorRenderersUI RenderersUI;
    EditorPaletteUI PaletteUI;
    LevelDataUI LevelDataUI;
    EditorComponentsUI ComponentsUI;
    EditorStatesUI ActionsUI;

    void Init();

    void AfterEditor(EditorSceneOld& editor, AssetManager& assetManager);
};

#endif //SHEEP_GOES_DEVILE_EDITOR_UI_H
