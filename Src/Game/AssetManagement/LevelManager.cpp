//
// Created by Kamil on 04.06.2026.
//
#include "LevelManager.h"
#include "Editor/EditorSceneOld.h"
#include "JSON.h"

Renderer& LevelData::GetRenderer(const size_t index)
{
    return Renderers[index];
}

size_t LevelData::size() const
{
    return Renderers.size();
}

void LevelData::AddRenderer(const Renderer& renderer, const int componentType)
{
    Renderers.push_back(renderer);
    Components.AddComponent(componentType);
}

void LevelData::SwapEntities(const size_t a, const size_t b)
{
    std::swap(Renderers[a], Renderers[b]);
    Components.Swap(a, b);
}

void to_json(JSON& j, LevelData& level)
{
    auto& renderers = j["renderers"] = JSON::array();
    for (size_t i = 0; i < level.size(); ++i)
    {
        auto& rendererJson = renderers[i] = JSON::object();
        const Renderer renderer = level.GetRenderer(i);
        to_json(rendererJson, renderer);

        JSON component = nullptr;
        const auto& [Type, Index] = level.Components.GetComponent(i);
#define X(e, v) case ComponentData::e: \
 component = level.Components.Get##v##Data(Index); \
 break;

        switch (Type)
        {
            ComponentNamesMacro(X)
            default:
                break;
        }
#undef X

        rendererJson["component_type"] = Type;
        rendererJson["component_data"] = component;
    }
}

void from_json(const JSON& j, LevelData& level)
{
    if (!j.contains("renderers"))
    {
        return;
    }

    const auto& renderersJson = j["renderers"];
    if (!renderersJson.is_array())
    {
        return;
    }

    for (const auto& rendererJson : renderersJson)
    {
        int componentType;
        ReadJsonValue(componentType, rendererJson, "component_type", 0);
        if (componentType >= ComponentData::COMPONENT_COUNT || componentType < 0)
        {
            componentType = 0;
        }

        level.AddRenderer(rendererJson, componentType);
    }
}

void LevelManager::LoadAll(EditorSceneOld& editor)
{
    Metadata.clear();
    Data.clear();

    std::filesystem::path path = RESOURCES_PATH;
    path += "Levels/";
    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
        if (!entry.is_regular_file())
        {
            continue;
        }

        auto& entryPath = entry.path();
        JSON map = ReadJson(entryPath.string().c_str());
        if (map.empty())
        {
            continue;
        }

        Metadata.push_back({entryPath.stem().string()});
        Data.push_back(map);
    }

    if (Data.empty())
    {
        Data.emplace_back();
        Metadata.push_back({"New Level"});
    }

    Load(editor, 0);
}

void LevelManager::Load(EditorSceneOld& editor, const int index) const
{
    editor.Reset();
    editor.CurrentLevel = index;
}

void LevelManager::Save(const EditorSceneOld& editor)
{
    const std::string s = RESOURCES_PATH "Levels/" + Metadata[editor.CurrentLevel].Name + ".json";
    SaveJson(Data[editor.CurrentLevel], s.c_str());
}
