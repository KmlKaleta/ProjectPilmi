//
// Created by Kamil on 04.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_LEVEL_MANAGER_H
#define SHEEP_GOES_DEVILE_LEVEL_MANAGER_H
#include "../EntityStorage.hpp"

struct LevelData
{
    EntityStorage Entities;

    LevelData() = default;
    LevelData(LevelData&&) = default;
    LevelData& operator=(LevelData&&) = default;

    LevelData Copy() const;
};

void to_json(JSON& j, const LevelData& level);

void from_json(const JSON& j, LevelData& level);

struct LevelManager
{
    std::vector<LevelData> Data;
    std::vector<std::string> Metadata;
    std::unordered_map<UUID, size_t> Ids;

    UUID CurrentLevelId;

    LevelData& CurrentLevel();

    void Load(UUID level);

    void LoadAll();

    void Save();

    void Rename(const std::string& newName);

    void Delete();

    void Create();
};

#endif //SHEEP_GOES_DEVILE_LEVEL_MANAGER_H
