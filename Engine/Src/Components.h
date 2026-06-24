//
// Created by Kamil on 18.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_COMPONENTS_H
#define SHEEP_GOES_DEVILE_COMPONENTS_H
#include "UUID.hpp"
#include "JSON.h"
#include "Fields/EntityRef.hpp"
#include "Fields/Range.hpp"

#define RequiredComponentNamesMacro(X) \
X(ID, IDComponent) \
X(TAG, TagComponent)

#define AdditionalComponentNamesMacro(X) \
X(PARALLAX, ParallaxComponent)

#define UtilityComponentNamesMacro(X) \
X(ENTITY_GROUP, EntityGroupComponent) \
X(ENTITY_GROUP_CHILD, EntityGroupChildComponent) \
X(ORDER, OrderComponent)

#define AllComponentNamesMacro(X) \
    RequiredComponentNamesMacro(X) \
    UtilityComponentNamesMacro(X) \
    AdditionalComponentNamesMacro(X)

enum class RequiredComponentType
{
#define X(e, t) e,
    RequiredComponentNamesMacro(X)
#undef X
    COUNT
};

enum class AdditionalComponentType
{
#define X(e, t) e,
    AdditionalComponentNamesMacro(X)
#undef X
    COUNT
};

enum class UtilityComponentType
{
#define X(e, t) e,
    UtilityComponentNamesMacro(X)
#undef X
    COUNT
};

enum class ComponentType
{
    None = 0,
#define X(e, t) e,
    AllComponentNamesMacro(X)
#undef X

    COUNT
};

struct IDComponent
{
    UUID Value;
};

void to_json(JSON& j, const IDComponent& component);

void from_json(const JSON& j, IDComponent& component);

bool operator==(const IDComponent& lhs, const IDComponent& rhs);

bool operator!=(const IDComponent& lhs, const IDComponent& rhs);

struct TagComponent
{
    std::string Value;
};

void to_json(JSON& j, const TagComponent& component);

void from_json(const JSON& j, TagComponent& component);

bool operator==(const TagComponent& lhs, const TagComponent& rhs);

bool operator!=(const TagComponent& lhs, const TagComponent& rhs);

struct OrderComponent
{
    uint32_t Value;

    operator size_t() const { return Value; }
};

void to_json(JSON& j, const OrderComponent& component);

void from_json(const JSON& j, OrderComponent& component);

struct ParallaxComponent
{
    Range<float> Strength = Range<float>(0.1f, 2.0f, 1);
};

void to_json(JSON& j, const ParallaxComponent& component);

void from_json(const JSON& j, ParallaxComponent& component);

bool operator==(const ParallaxComponent& lhs, const ParallaxComponent& rhs);

bool operator!=(const ParallaxComponent& lhs, const ParallaxComponent& rhs);

struct EntityGroupComponent
{
    std::vector<EntityRef> Entities;
};

void to_json(JSON&, const EntityGroupComponent&);

void from_json(const JSON&, EntityGroupComponent&);

struct EntityGroupChildComponent
{
    EntityRef Value;
};

void to_json(JSON&, const EntityGroupChildComponent&);

void from_json(const JSON&, EntityGroupChildComponent&);

#endif //SHEEP_GOES_DEVILE_COMPONENTS_H
