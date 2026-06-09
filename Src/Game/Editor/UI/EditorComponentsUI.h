//
// Created by Kamil on 04.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_EDITOR_COMPONENTS_UI_H
#define SHEEP_GOES_DEVILE_EDITOR_COMPONENTS_UI_H

struct LevelData;
struct EditorScene;

struct EditorComponentsUI
{
    float GetHeight(const EditorScene& editor, float padding) const;

    void Draw(float width, float contentX, float contentY, float padding, const EditorScene& editor, LevelData& level) const;
};
#endif //SHEEP_GOES_DEVILE_EDITOR_COMPONENTS_UI_H
