//
// Created by Kamil on 04.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_LEVEL_MANAGER_H
#define SHEEP_GOES_DEVILE_LEVEL_MANAGER_H
#include "../Renderer.h"
#include <vector>
#include <string>
#include "ComponentData.h"


struct EditorScene;

struct LevelMetadata
{
    std::string Name;
};

struct LevelData
{
    Renderer& GetRenderer(size_t index);

    size_t size() const;

    void AddRenderer(const Renderer& renderer, int componentType = ComponentData::COMPONENT_NONE);

    void SwapEntities(size_t a, size_t b);

    ComponentStorage Components;

private:
    std::vector<Renderer> Renderers;
};

void to_json(JSON& j, const LevelData& level);

void from_json(const JSON& j, LevelData& level);

struct LevelManager
{
    std::vector<LevelData> Data = {};
    std::vector<LevelMetadata> Metadata = {};

    void LoadAll(EditorScene& editor);

    void Load(EditorScene& editor, int index) const;

    void Save(const EditorScene& editor);

    void Reload();
};
#endif //SHEEP_GOES_DEVILE_LEVEL_MANAGER_H
