//
// Created by Kamil on 05.07.2026.
//

#ifndef SHEEP_GOES_DEVILE_EDITOR_MENU_H
#define SHEEP_GOES_DEVILE_EDITOR_MENU_H
struct UndoRedoContext;
struct EditorUndoRedo;

struct EditorMenuUI
{
    void Draw(EditorUndoRedo& undoRedo, UndoRedoContext& context) const;
};
#endif //SHEEP_GOES_DEVILE_EDITOR_MENU_H
