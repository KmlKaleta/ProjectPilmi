//
// Created by Kamil on 15.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_EDITOR_HIERARCHY_UI_H
#define SHEEP_GOES_DEVILE_EDITOR_HIERARCHY_UI_H

struct AssetManager;
struct EditorHierarchy;
struct EntitySelection;

struct EditorHierarchyUI
{
    void Draw(EditorHierarchy& hierarchy, EntitySelection& selection, AssetManager& assetManager) const;
};
#endif //SHEEP_GOES_DEVILE_EDITOR_HIERARCHY_UI_H
