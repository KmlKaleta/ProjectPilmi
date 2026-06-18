//
// Created by Kamil on 16.06.2026.
//
#include "EditorWindow.h"

bool EditorWindow::Init()
{
    Ui.Init();
    return Editor.Init();
}

bool EditorWindow::Update()
{
    if (Editor.Update())
    {
        Ui.Draw();
        return true;
    }
    return false;
}

void EditorWindow::Close()
{
    Editor.Close();
}
