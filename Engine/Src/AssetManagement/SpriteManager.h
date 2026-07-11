//
// Created by Kamil on 30.05.2026.
//

#ifndef SHEEP_GOES_DEVILE_SPRITES_MANAGER_H
#define SHEEP_GOES_DEVILE_SPRITES_MANAGER_H
#include <string>
#include <utility>
#include <vector>
#include <unordered_map>

#include "UUID.hpp"
#include "../SpriteData.h"

struct SpriteMetadata
{
    std::string Name;

    SpriteMetadata() = default;
    SpriteMetadata(std::string  name) : Name(std::move(name)) {}
};

void to_json(JSON& j, const SpriteMetadata& metadata);

void from_json(const JSON& j, SpriteMetadata& metadata);

struct SpriteManager
{
    std::vector<SpriteData> Data = {};
    std::vector<SpriteMetadata> Metadata = {};
    std::unordered_map<UUID, size_t> Ids = {};

    SpriteData FromId(const UUID id) const
    {
        const auto& it = Ids.find(id);
        if (it == Ids.end())
            return {};

        return Data[it->second];
    }

    void LoadAll();

private:
    void IterateDirectory(const std::filesystem::path& path);
};

#endif //SHEEP_GOES_DEVILE_SPRITES_MANAGER_H
