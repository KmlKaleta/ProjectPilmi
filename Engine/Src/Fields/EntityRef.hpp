//
// Created by Kamil on 24.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_ENTITY_REF_HPP
#define SHEEP_GOES_DEVILE_ENTITY_REF_HPP
#include "UUID.hpp"

struct EntityRef
{
    UUID ID;

    EntityRef() = default;
    EntityRef(const UUID id) : ID(id) {}

    EntityRef(const EntityRef&) = default;
    EntityRef(EntityRef&&) = default;

    EntityRef& operator=(const EntityRef&) = default;
    EntityRef& operator=(EntityRef&&) = default;
};

#endif //SHEEP_GOES_DEVILE_ENTITY_REF_HPP
