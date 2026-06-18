//
// Created by Kamil on 16.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_EDITOR_COMPONENTS_UI_H
#define SHEEP_GOES_DEVILE_EDITOR_COMPONENTS_UI_H
#include "EditorUIPanel.h"

struct Rectangle;

struct EditorComponentsUI : private EditorUIPanel
{
    void Draw() const;
};
#endif //SHEEP_GOES_DEVILE_EDITOR_COMPONENTS_UI_H
