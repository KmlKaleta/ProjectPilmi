//
// Created by Kamil on 15.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_EDITOR_WINDOW_H
#define SHEEP_GOES_DEVILE_EDITOR_WINDOW_H
#include "EditorApplication.h"
#include "Ui/EditorApplicationUI.h"

struct EditorWindow
{
    EditorApplication Editor;
    EditorApplicationUI Ui;

    bool Init();
    bool Update();
    void Close();
};

#endif //SHEEP_GOES_DEVILE_EDITOR_WINDOW_H
