//
// Created by Kamil on 18.06.2026.
//
#include "Components.h"

void to_json(JSON& j, const IDComponent& component)
{
    j["value"] = component.Value;
}

void from_json(const JSON& j, IDComponent& component)
{
    ReadJsonValue(component.Value.Value, j, "value", uint64_t());
}

bool operator==(const IDComponent& lhs, const IDComponent& rhs)
{
    return lhs.Value == rhs.Value;
}

bool operator!=(const IDComponent& lhs, const IDComponent& rhs)
{
    return !(lhs == rhs);
}

void to_json(JSON& j, const TagComponent& component)
{
    j["value"] = component.Value;
}

void from_json(const JSON& j, TagComponent& component)
{
    ReadJsonValue(component.Value, j, "value", std::string("No Name"));
}

bool operator==(const TagComponent& lhs, const TagComponent& rhs)
{
    return lhs.Value == rhs.Value;
}

bool operator!=(const TagComponent& lhs, const TagComponent& rhs)
{
    return !(lhs == rhs);
}

void to_json(JSON& j, const OrderComponent& component)
{
    j = component.Value;
}

void from_json(const JSON& j, OrderComponent& component)
{
    ReadJsonValue(component.Value, j, "value", std::numeric_limits<uint32_t>::max());
}

void to_json(JSON& j, const ParallaxComponent& component)
{
    j["strength"] = component.Strength;
}

void from_json(const JSON& j, ParallaxComponent& component)
{
    ReadJsonValue(component.Strength, j, "strength", component.Strength);
}

bool operator==(const ParallaxComponent& lhs, const ParallaxComponent& rhs)
{
    return lhs.Strength.Get() == rhs.Strength.Get();
}

bool operator!=(const ParallaxComponent& lhs, const ParallaxComponent& rhs)
{
    return !(lhs == rhs);
}

void to_json(JSON& j, const EntityGroupComponent& component)
{
    j = JSON::array();
    for (const auto& [ID] : component.Entities)
    {
        j.push_back(ID);
    }
}

void from_json(const JSON& j, EntityGroupComponent& component)
{
    if (!j.is_array())
    {
        return;
    }

    for (const auto& ID : j)
    {
        UUID id{};
        from_json(ID, id);

        if (id != 0){
            component.Entities.push_back({id});
        }
    }
}

void to_json(JSON& j, const EntityGroupChildComponent& component)
{
    j = JSON::object();
}

void from_json(const JSON&, EntityGroupChildComponent&)
{
}
