//
// Created by Kamil on 28.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_RENDERING_SYSTEM_H
#define SHEEP_GOES_DEVILE_RENDERING_SYSTEM_H
#include <vector>
#include "entt/entity/registry.hpp"

struct GameSystemsUpdateArgs;

struct RenderingSystem
{
    std::vector<entt::entity> Order;

    void Update(GameSystemsUpdateArgs& args);
};
#endif //SHEEP_GOES_DEVILE_RENDERING_SYSTEM_H
