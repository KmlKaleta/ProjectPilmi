//
// Created by Kamil on 18.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_COMPONENTS_H
#define SHEEP_GOES_DEVILE_COMPONENTS_H
#include "AnimationData.hpp"
#include "UUID.hpp"
#include "JSON.h"
#include "Renderer.h"
#include "Fields/EntityRef.hpp"
#include "Fields/Range.hpp"
#include "Fields/WorldPosition.hpp"

#define RequiredComponentNamesMacro(X) \
X(ID, IDComponent) \
X(TAG, TagComponent)

#define AdditionalComponentNamesMacro(X) \
X(PARALLAX, ParallaxComponent) \
X(RENDERER, RendererComponent) \
X(MOVE_SPEED, MoveSpeedComponent) \
X(PATROL, PatrolComponent) \
X(ROUND, RoundComponent) \
X(ANIMATOR, AnimatorComponent)

#define UtilityComponentNamesMacro(X) \
X(ENTITY_GROUP, EntityGroupComponent) \
X(ENTITY_GROUP_CHILD, EntityGroupChildComponent) \
X(ORDER, OrderComponent)

#define TagComponentNamesMacro(X) \
X(MyTag, MyTagComponent)

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

enum class TagComponentType
{
#define X(e, t) e,
    TagComponentNamesMacro(X)
#undef X
    COUNT
};

enum class ComponentType
{
    None = 0,
#define X(e, t) e,
    AllComponentNamesMacro(X)
    TagComponentNamesMacro(X)
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

    operator size_t() const
    {
        return Value;
    }
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

struct RendererComponent
{
    uint32_t LayerOrder = 0;
    Renderer Data;
};

void to_json(JSON& j, const RendererComponent& component);

void from_json(const JSON& j, RendererComponent& component);

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

struct MoveSpeedComponent
{
    Range<float> Value = Range<float>(10.f, 2000.0f, 200);
};

void to_json(JSON& j, const MoveSpeedComponent& component);

void from_json(const JSON& j, MoveSpeedComponent& component);

struct PatrolComponent
{
    WorldPosition From = {0, 0};
    WorldPosition To = {500, 0};
    bool Reversed = false;
};

void to_json(JSON& j, const PatrolComponent& component);

void from_json(const JSON& j, PatrolComponent& component);

struct RoundComponent
{
    WorldPosition Center;
    Range<float> Radius = Range<float>(10.f, 5000.0f, 400);
    float T = 0;
};

void to_json(JSON& j, const RoundComponent& component);

void from_json(const JSON& j, RoundComponent& component);

struct AnimatorComponent
{
    AnimationData Data;
    int Animation{};
    Range<float> FrameTime = Range(0.01f, 1.f, 0.1f);
};

void to_json(JSON& j, const AnimatorComponent& component);

void from_json(const JSON& j, AnimatorComponent& component);

struct MyTagComponent{};

#endif //SHEEP_GOES_DEVILE_COMPONENTS_H
