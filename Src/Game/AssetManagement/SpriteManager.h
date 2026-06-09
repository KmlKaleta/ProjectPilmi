//
// Created by Kamil on 30.05.2026.
//

#ifndef SHEEP_GOES_DEVILE_SPRITES_MANAGER_H
#define SHEEP_GOES_DEVILE_SPRITES_MANAGER_H
#include <string>
#include <vector>
#include <unordered_map>

#include "../SpriteData.h"
#include "../Utility.hpp"

struct SpriteMetadata
{
    std::string Name;
    std::string Path;
};

void to_json(JSON& j, const SpriteMetadata& metadata);

void from_json(const JSON& j, SpriteMetadata& metadata);

struct SpriteManager
{
    std::vector<SpriteData> Data = {};
    std::vector<SpriteMetadata> Metadata = {};
    std::unordered_map<uint64_t, size_t> Ids = {};

    SpriteData FromId(const uint64_t id) const
    {
        return Data[Ids.at(id)];
    }

    void LoadAll();

    void Reload();

    void SaveAll() const;
};

#endif //SHEEP_GOES_DEVILE_SPRITES_MANAGER_H
