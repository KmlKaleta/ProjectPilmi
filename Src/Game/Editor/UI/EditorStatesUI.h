//
// Created by Kamil on 10.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_EDITOR_ACTIONS_UI_H
#define SHEEP_GOES_DEVILE_EDITOR_ACTIONS_UI_H

struct EditorSceneOld;
struct LevelData;

struct EditorStatesUI
{
    float GetHeight(EditorSceneOld& editor, LevelData& levelData) const;

    void Draw(float contentX, float contentY, float width, float padding, EditorSceneOld& editor, LevelData& levelData) const;
};

#endif //SHEEP_GOES_DEVILE_EDITOR_ACTIONS_UI_H
