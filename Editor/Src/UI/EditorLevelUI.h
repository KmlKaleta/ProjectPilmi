//
// Created by Kamil on 16.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_EDITOR_LEVEL_UI_H
#define SHEEP_GOES_DEVILE_EDITOR_LEVEL_UI_H
struct LevelManager;
struct  EditorUndoRedo;

struct EditorLevelUI
{
    void Draw(LevelManager& levels, EditorUndoRedo& undoRedo) const;
};

#endif //SHEEP_GOES_DEVILE_EDITOR_LEVEL_UI_H
