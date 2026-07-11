//
// Created by Kamil on 16.06.2026.
//
#include "EditorWindow.h"
#include "EditorUndoRedo.hpp"

bool EditorWindow::Init()
{
    return Editor.Init();
}

bool EditorWindow::Update()
{
    auto context = UndoRedoContext{Editor.Assets.Levels.CurrentLevel().Entities, Editor.Selection, Editor.Assets};
    Ui.Draw(Editor, context);
    return Editor.Update(context);
}

void EditorWindow::Close()
{
    Editor.Close();
}
