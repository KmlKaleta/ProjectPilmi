//
// Created by Kamil on 04.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_LEVEL_DATA_UI_H
#define SHEEP_GOES_DEVILE_LEVEL_DATA_UI_H

struct LevelManager;
struct EditorSceneOld;
struct Rectangle;

struct LevelDataUI
{
    constexpr static float Width = 150.f;

    Rectangle GetRect() const;

    float GetHeight() const;

    void Draw(EditorSceneOld& editor, LevelManager& levelManager) const;
};
#endif //SHEEP_GOES_DEVILE_LEVEL_DATA_UI_H
