//
// Created by Kamil on 09.06.2026.
//
#include "ComponentData.h"
#include "raymath.h"
#include "Renderer.h"

void to_json(JSON& j, const ParallaxComponent& parallax)
{
    j["strength"] = parallax.Strength;
}

void from_json(const JSON& j, ParallaxComponent& parallax)
{
    const float value = j.value("strength", 0.f);
    parallax.Strength.Set(value);
}

void to_json(JSON& j, const MovementComponent& movement)
{
    j["speed"] = movement.Speed;
}

void from_json(const JSON& j, MovementComponent& movement)
{
    const float value = j.value("speed", 0.f);
    movement.Speed.Set(value);
}

void MovementComponent::Update(Renderer& renderer, const float deltaTime) const
{
    renderer.Position += Vector2Normalize(Target - renderer.Position) * (deltaTime * Speed.Get());
}

bool MovementComponent::IsTargetReached(const Renderer& renderer, const float deltaTime) const
{
    const float frameDistance = Speed.Get() * deltaTime;
    return Vector2DistanceSqr(renderer.Position, Target) <= frameDistance * frameDistance + 0.0001f;
}

ComponentData ComponentStorage::GetComponent(const size_t index) const
{
    assert(index < Components.size());
    return Components[index];
}

void ComponentStorage::Swap(const size_t a, const size_t b)
{
    assert(a < Components.size() && b < Components.size());

    std::swap(Components[a], Components[b]);
}

template<typename T>
void RemoveAndSwapBack(std::vector<T>& vector, const size_t index)
{
    std::swap(vector[index], vector[vector.size() - 1]);
    vector.pop_back();
}

void ComponentStorage::RemoveAt(const int type, const size_t index)
{
    if (type == 0)
    {
        return;
    }

#define X(e, v) case ComponentData::e: \
RemoveAndSwapBack(v##Vector, index); \
break;

    switch (type)
    {
        RequiredComponentNamesMacro(X)
        default:
            break;
    }
#undef X

    for (auto& [Type, Index] : Components)
    {
        if (Type == type && Index > index)
        {
            Index--;
        }
    }
}

template<typename T>
void AddElement(size_t& index, std::vector<T>& vector)
{
    index = vector.size();
    vector.emplace_back();
}

void ComponentStorage::ChangeType(const size_t index, const int value)
{
    assert(index < Components.size());
    auto& [Type, Index] = Components[index];
    if (Type == value)
    {
        return;
    }

    RemoveAt(Type, Index);
#define X(e, v)case ComponentData::e: \
AddElement(Index, v##Vector); \
break;
    switch (value)
    {
        RequiredComponentNamesMacro(X)
        default:
            Index = 0;
            break;
    }
#undef X

    Type = value;
}

void ComponentStorage::AddComponent(const int type)
{
    assert(type >= 0 && type < ComponentData::COMPONENT_COUNT);

    size_t index = 0;
#define X(e, v)case ComponentData::e: \
AddElement(index, v##Vector); \
break;
    switch (type)
    {
        RequiredComponentNamesMacro(X)
        default:
            break;
    }
#undef X

    Components.push_back({type, index});
}

#define X(e, v) v& ComponentStorage::Get##v##Data(size_t index) \
    { \
        assert(index < v##Vector.size()); \
        return v##Vector[index]; \
    }
RequiredComponentNamesMacro(X)
#undef X
