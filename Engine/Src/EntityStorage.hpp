//
// Created by Kamil on 15.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_ENTITY_STORAGE_H
#define SHEEP_GOES_DEVILE_ENTITY_STORAGE_H
#include <entt/entt.hpp>
#include "JSON.h"
#include "Components.h"
#include "StringUtility.hpp"
#include "UUIDFactory.hpp"

struct EntityStorage
{
    entt::registry Registry = {};
    std::unordered_map<UUID, entt::entity> EntityMap = {};

    entt::entity GetEntity(const UUID id) const
    {
        const auto& it = EntityMap.find(id);
        if (it == EntityMap.end())
            return entt::null;

        return it->second;
    }

    entt::entity CreateEntity(UUIDFactory& factory)
    {
        return  CreateEntity(factory.Get());
    }

    entt::entity CreateEntity(const UUID id)
    {
        const entt::entity entity = Registry.create();
        Registry.emplace<TagComponent>(entity, TagComponent{"Entity"});
        Registry.emplace<OrderComponent>(entity, OrderComponent{static_cast<uint32_t>(EntityMap.size())});

        EntityMap[id] = entity;
        return entity;
    }

    void AddEntity(const UUID id, const entt::entity entity)
    {
        TagComponent& tagComponent = Registry.get_or_emplace<TagComponent>(entity);
        if (IsNullOrWhiteSpace(tagComponent.Value))
        {
            tagComponent.Value = "Entity";
        }

        EntityMap[id] = entity;
    }

    void DestroyEntity(const UUID id)
    {
        if (const entt::entity entity = GetEntity(id); entity != entt::null)
        {
            Registry.destroy(entity);
            EntityMap.erase(id);
        }
    }
};

inline void to_json(JSON& out, const EntityStorage& storage)
{
    // Map to hold entity JSON data dynamically by their ID
    std::unordered_map<entt::id_type, JSON> entity_map;

    // 1. Serialize Standard Components
#define X(e, t) \
if (auto* pool = storage.Registry.storage<t>()) { \
for (auto [entity, component] : pool->each()) { \
entity_map[entt::to_integral(entity)][#t] = component; \
} \
}
    AllComponentNamesMacro(X)
#undef X

    // 2. Serialize Tag Components
#define X(e, t) \
if (auto* pool = storage.Registry.storage<t>()) { \
for(auto [entity] : pool->each()) { \
entity_map[entt::to_integral(entity)]["tags"].emplace_back(#t); \
} \
}
    TagComponentNamesMacro(X)
#undef X

    for (const auto& [uuid, entity] : storage.EntityMap) {
        auto integral_id = entt::to_integral(entity);

        entity_map[integral_id]["EntityId"] = uuid;
    }

    // 3. Collect into your final JSON array
    JSON final_array = JSON::array();
    for (auto& [id, json_obj] : entity_map)
    {
        // EnTT entities must keep track of their ID during serialization
        json_obj["id"] = id;
        final_array.push_back(std::move(json_obj));
    }
    out = final_array;
}

inline UUID GetId(UUIDFactory& factory, const JSON& j)
{
    uint64_t value;
    const UUID d = factory.Get();
    ReadJsonValue(value, j, "EntityId", d.Value);

    return value == 0 ? d : UUID{value};
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

    for (const auto& entityJson : j)
    {
        if (!entityJson.is_object() || entityJson.empty())
        {
            continue;
        }

        const entt::entity entity = storage.Registry.create();

        // 1. Optimized Data Components (Single JSON lookup via .find())
#define X(e, t) \
if (auto it = entityJson.find(#t); it != entityJson.end()) \
{ \
t component{}; \
/* Pass the found sub-iterator directly to your reader if possible, */ \
/* or keep using ReadJsonValue(component, entityJson, #t, component); */ \
ReadJsonValue(component, entityJson, #t, component); \
storage.Registry.emplace<t>(entity, component); \
}
        AllComponentNamesMacro(X)
#undef X

        // 2. Optimized Tags via Compile-Time Map
        if (auto it = entityJson.find("tags"); it != entityJson.end() && it->is_array())
        {
            for (const auto& tag : *it)
            {
                if (!tag.is_string()) continue;

                std::string tagString = tag.get<std::string>();

                // We create a fast lookup function using a switch or static map inside a lambda
                auto emplace_tag_by_name = [&](const std::string& name, entt::entity ent)
                {
                    // Using an internal macro to build a clean string-to-type dispatcher
#define X(e, t) if (name == #t) { storage.Registry.emplace<t>(ent); return; }
                    TagComponentNamesMacro(X)
#undef X
                };

                emplace_tag_by_name(tagString, entity);
            }
        }

        const UUID id = GetId(factory, entityJson);

        storage.AddEntity(id, entity);
    }
}

#endif //SHEEP_GOES_DEVILE_ENTITY_STORAGE_H
