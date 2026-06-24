//
// Created by Kamil on 15.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_ENTITY_STORAGE_H
#define SHEEP_GOES_DEVILE_ENTITY_STORAGE_H
#include <entt/entt.hpp>
#include "JSON.h"
#include "Components.h"
#include "UUIDFactory.hpp"

struct EntityStorage
{
    entt::registry Registry;
    std::unordered_map<UUID, entt::entity> EntityMap;

    entt::entity CreateEntity(UUIDFactory& factory)
    {
        const entt::entity entity = Registry.create();
        const auto id = factory.Get();
        Registry.emplace<IDComponent>(entity, IDComponent{id});
        Registry.emplace<TagComponent>(entity, TagComponent{"No Name"});
        Registry.emplace<OrderComponent>(entity, EntityMap.size());

        EntityMap[id] = entity;
        return entity;
    }
};

inline void to_json(JSON& out, const EntityStorage& storage)
{
    JSON array = out["entities"] = JSON::array();
    const auto view = storage.Registry.view<entt::entity>();
    for (const auto entity : view)
    {
        JSON j = array.emplace_back(JSON::object());
#define  X(e, t) if (const auto* component = storage.Registry.try_get<t>(entity)) \
    { \
        j[#t] = *component; \
    }
        AllComponentNamesMacro(X)
#undef X
    }
}

inline IDComponent GetIdComponent(UUIDFactory& factory, const JSON& j)
{
    uint64_t value;
    const UUID d = factory.Get();
    ReadJsonValue(value, j, "IDComponent", d.Value);
    return IDComponent{value};
}

inline TagComponent GetTagComponent(const JSON& j)
{
    std::string tag = "No Name";
    ReadJsonValue(tag, j, "TagComponent", tag);
    return TagComponent{tag};
}

inline void from_json(const JSON& j, EntityStorage& storage)
{
    UUIDFactory factory;
    if (!j.contains("entities"))
    {
        return;
    }

    const JSON& array = j["entities"];
    if (!array.is_array())
    {
        return;
    }

    for (const auto& entityJson : array)
    {
        if (!entityJson.is_object() || entityJson.empty())
        {
            continue;
        }

        const entt::entity entity = storage.CreateEntity(factory);

#define X(e, t) if (entityJson.contains(#t)) \
            { \
                t component{}; \
                ReadJsonValue(component, entityJson, #t, component); \
                storage.Registry.emplace<t>(entity, component); \
            }
        AllComponentNamesMacro(X)
#undef X
    }
}

#endif //SHEEP_GOES_DEVILE_ENTITY_STORAGE_H
