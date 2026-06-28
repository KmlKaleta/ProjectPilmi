//
// Created by Kamil on 15.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_EDITOR_HIERARCHY_H
#define SHEEP_GOES_DEVILE_EDITOR_HIERARCHY_H
#include <vector>
#include <entt/entt.hpp>

struct EntityStorage;

struct EditorHierarchy
{
    std::vector<entt::entity> Order;
};

#endif //SHEEP_GOES_DEVILE_EDITOR_HIERARCHY_H
