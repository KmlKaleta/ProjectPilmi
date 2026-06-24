//
// Created by Kamil on 16.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_EDITOR_COMPONENTS_UI_H
#define SHEEP_GOES_DEVILE_EDITOR_COMPONENTS_UI_H

struct AssetManager;
struct EntitySelection;

struct EditorComponentsUI
{
    void Draw(const EntitySelection& selection, AssetManager& assetManager) const;
};
#endif //SHEEP_GOES_DEVILE_EDITOR_COMPONENTS_UI_H
