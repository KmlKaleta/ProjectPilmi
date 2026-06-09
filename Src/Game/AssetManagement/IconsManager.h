//
// Created by Kamil on 30.05.2026.
//

#ifndef SHEEP_GOES_DEVILE_ICONS_MANAGER_H
#define SHEEP_GOES_DEVILE_ICONS_MANAGER_H

#include <cstdint>
#include <unordered_map>
#include "../SpriteData.h"

struct IconsManager
{
    void LoadAll();
    void Reload();

    std::vector<SpriteData> Icons = {};
    std::unordered_map<uint64_t, size_t> Ids = {};

    SpriteData FromId(const uint64_t id) const;
};

#endif //SHEEP_GOES_DEVILE_ICONS_MANAGER_H
