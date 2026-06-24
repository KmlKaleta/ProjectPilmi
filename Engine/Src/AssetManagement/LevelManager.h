//
// Created by Kamil on 04.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_LEVEL_MANAGER_H
#define SHEEP_GOES_DEVILE_LEVEL_MANAGER_H
#include "../EntityStorage.h"

struct LevelManager
{
    EntityStorage Entities;

    void LoadAll();

    void Load();

    void Save();

    void Reload();
};
// #include "../Renderer.h"
// #include <vector>
// #include <string>
// #include "ComponentData.h"
// #include "GameState.h"
//
//
// struct EditorSceneOld;
//
// struct LevelMetadata
// {
//     std::string Name;
// };
//
// struct LevelData
// {
//     Renderer& GetRenderer(size_t index);
//
//     size_t size() const;
//
//     void AddRenderer(const Renderer& renderer, int componentType = ComponentData::COMPONENT_NONE);
//
//     void SwapEntities(size_t a, size_t b);
//
//     ComponentStorage Components;
//
//     std::vector<GameState> InitActions;
//     std::vector<GameState> UpdateActions;
// private:
//     std::vector<Renderer> Renderers;
// };
//
// void to_json(JSON& j, const LevelData& level);
//
// void from_json(const JSON& j, LevelData& level);
//
// struct LevelManager
// {
//     std::vector<LevelData> Data = {};
//     std::vector<LevelMetadata> Metadata = {};
//
//     void LoadAll(EditorSceneOld& editor);
//
//     void Load(EditorSceneOld& editor, int index) const;
//
//     void Save(const EditorSceneOld& editor);
//
//     void Reload();
// };
#endif //SHEEP_GOES_DEVILE_LEVEL_MANAGER_H
