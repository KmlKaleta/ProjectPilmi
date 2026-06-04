//
// Created by Kamil on 30.05.2026.
//
#include "SpriteManager.h"

static void MapSprite(SpriteData& sprite, SpriteMetadata& metadata, const JSON& data)
{
    auto value = data["name"];
    if (value.is_string())
    {
        metadata.Name = value.get<std::string>();
    }

    value = data["scale"];
    if (value.is_number())
    {
        sprite.Scale = value.get<float>();
    }

    value = data["pivot"];
    if (value.is_array() && value.size() == 2)
    {
        auto item = value[0];
        if (item.is_number())
        {
            sprite.Pivot.x = item.get<float>();
        }

        item = value[1];
        if (item.is_number())
        {
            sprite.Pivot.y = item.get<float>();
        }
    }

    value = data["rowCounts"];
    if (value.is_array())
    {
        sprite.RowCounts.resize(value.size());
        for (size_t i = 0; i < value.size(); i++)
        {
            auto& item = value[i];
            sprite.RowCounts[i] = item.is_number_integer() ? std::abs(item.get<int>()) : 1;
        }
    }

    value = data["rowCountMax"];
    if (value.is_number_integer())
    {
        sprite.RowCountMax = std::abs(value.get<int>());
    }
}

void SpriteManager::LoadAll()
{
    std::filesystem::path path = RESOURCES_PATH;
    path += "Sprites/";
    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
        if (!entry.is_regular_file())
        {
            continue;
        }

        SpriteData sprite;
        SpriteMetadata metadata;

        auto& entryPath = entry.path();

        auto entryPathStr = entryPath.string();
        sprite.Tex = LoadTexture(entryPathStr.c_str());
        metadata.Path = entryPath.filename().string();

        std::string configPath{RESOURCES_PATH "Sprites/Configs/"};
        configPath += metadata.Path + ".json";
        const char* configChars = configPath.c_str();
        JSON j = ReadJson(configChars,
                          R"({"scale": 1, "pivot": [0,0], "rowCounts" : [1], "rowCountMax" : 1, "name" : "No Name"})");

        MapSprite(sprite, metadata, j);
        Ids[StringToHash(metadata.Path)] = Sprites.size();
        Sprites.push_back(sprite);
        Metadata.push_back(metadata);
    }
}

void SpriteManager::Reload()
{
    for (const auto & sprite : Sprites)
    {
        UnloadTexture(sprite.Tex);
    }
    *this = SpriteManager();
    LoadAll();
}

void SpriteManager::SaveAll() const
{
    for (const auto& [id, index] : Ids)
    {
        SpriteData sprite = Sprites[index];
        auto [Name, Path] = Metadata[index];
        JSON j = {
            {"name", Name},
            {"scale", sprite.Scale},
            {"pivot", {sprite.Pivot.x, sprite.Pivot.y}},
            {"rowCounts", sprite.RowCounts},
            {"rowCountMax", sprite.RowCountMax},
        };

        std::string s = RESOURCES_PATH "Sprites/Configs/" + Path + ".json";
        SaveJson(j, s.c_str());
    }
}
