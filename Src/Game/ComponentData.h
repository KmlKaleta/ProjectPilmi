//
// Created by Kamil on 09.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_COMPONENT_DATA_H
#define SHEEP_GOES_DEVILE_COMPONENT_DATA_H

#include <raylib.h>
#include <vector>
#include "Editor/EditorFields.h"
#include "AnimationData.h"
#include "include/visit_struct/visit_struct.hpp"

#define RequiredComponentNamesMacro(X) \
X(COMPONENT_MOVEMENT, MovementComponent) \
X(COMPONENT_PARALLAX, ParallaxComponent)

struct Renderer;

struct ComponentData
{
    int Type = 0;
    size_t Index = 0;

    enum
    {
        COMPONENT_NONE = 0,
#define X(e, v) e,
        RequiredComponentNamesMacro(X)
#undef X
        COMPONENT_COUNT
    };
};

struct ParallaxComponent
{
    Range Strength{0.01f, 5, 1};
};

void to_json(JSON& j, const ParallaxComponent& parallax);

void from_json(const JSON& j, ParallaxComponent& parallax);

VISITABLE_STRUCT(ParallaxComponent, Strength);

struct MovementComponent
{
    Range Speed{0.01f, 500, 100};
    Vector2 Target = {};
    AnimationData Animation;

    void Update(Renderer& renderer, float deltaTime) const;

    bool IsTargetReached(const Renderer& renderer, float deltaTime) const;
};

void to_json(JSON& j, const MovementComponent& movement);

void from_json(const JSON& j, MovementComponent& movement);

VISITABLE_STRUCT(MovementComponent, Speed);

struct ComponentStorage
{
    ComponentData GetComponent(size_t index) const;

    void Swap(size_t a, size_t b);

    void ChangeType(size_t index, int value);

    void AddComponent(int type);

#define X(e, v) v& Get##v##Data(size_t index);
    RequiredComponentNamesMacro(X)
#undef X

private:
    void RemoveAt(int type, size_t index);

    std::vector<ComponentData> Components;
#define X(e, v) std::vector<v> v##Vector;
    RequiredComponentNamesMacro(X)
#undef X
};

#endif //SHEEP_GOES_DEVILE_COMPONENT_DATA_H
