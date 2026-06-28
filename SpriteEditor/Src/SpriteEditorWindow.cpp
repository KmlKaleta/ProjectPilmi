//
// Created by Kamil on 24.06.2026.
//
#include "SpriteEditorWindow.h"

void SpriteEditorWindow::Init()
{
    Explorer.Refresh();
}

void SpriteEditorWindow::Update()
{
    ExplorerUI.Draw(Explorer, Editor);
    EditorUI.Draw(Editor, Explorer);
}
