//
// Created by Kamil on 04.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_EDITOR_RENDERERS_UI_H
#define SHEEP_GOES_DEVILE_EDITOR_RENDERERS_UI_H
struct LevelData;
struct EditorSceneOld;
struct SpriteManager;

struct EditorRenderersUI
{
    float GetHeight(const EditorSceneOld& editor, float padding) const;

    void Draw(float width, float contentX, float contentY, float padding, EditorSceneOld& editor, LevelData& levelData,
              const SpriteManager& sprites) const;
};
#endif //SHEEP_GOES_DEVILE_EDITOR_RENDERERS_UI_H
