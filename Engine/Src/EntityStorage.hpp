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

    void AddEntity(UUIDFactory& factory, entt::entity entity)
    {
        IDComponent& idComponent = Registry.get_or_emplace<IDComponent>(entity);
        if (idComponent.Value == 0)
        {
            idComponent.Value = factory.Get();
        }

        TagComponent& tagComponent = Registry.get_or_emplace<TagComponent>(entity);
        if (IsNullOrWhiteSpace(tagComponent.Value))
        {
            tagComponent.Value = "No Name";
        }

        OrderComponent& orderComponent = Registry.get_or_emplace<OrderComponent>(entity);

        EntityMap[idComponent.Value] = entity;
    }
};

inline void to_json(JSON& out, const EntityStorage& storage)
{
    JSON array = JSON::array();
    const auto view = storage.Registry.view<entt::entity>();
    for (const auto entity : view)
    {
        JSON& j = array.emplace_back(JSON::object());
#define  X(e, t) if (const auto* component = storage.Registry.try_get<t>(entity)) \
    { \
        j[#t] = *component; \
    }
        AllComponentNamesMacro(X)
#undef X

        JSON& tags = j["tags"] = JSON::array();

#define X(e, t) if (storage.Registry.all_of<t>(entity)) \
    { \
        tags.emplace_back(#t); \
    }
        TagComponentNamesMacro(X)
#undef X
    }
    out = array;
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

    for (const auto& entityJson : j)
    {
        if (!entityJson.is_object() || entityJson.empty())
        {
            continue;
        }

        const entt::entity entity = storage.Registry.create();

#define X(e, t) if (entityJson.contains(#t)) \
            { \
                t component{}; \
                ReadJsonValue(component, entityJson, #t, component); \
                storage.Registry.emplace<t>(entity, component); \
            }
        AllComponentNamesMacro(X)
#undef X
        if (entityJson.contains("tags"))
        {
            JSON tags = entityJson["tags"];
            if (tags.is_array() && !tags.empty())
            {
                for (const auto& tag : tags)
                {
                    if (tag.is_string())
                    {
                        std::string tagString = tag;
#define X(e, t) if (tagString == #t) \
    { \
        storage.Registry.emplace<t>(entity); \
    }
                        TagComponentNamesMacro(X)
#undef X
                    }
                }
            }
        }
        storage.AddEntity(factory, entity);
    }
}

#endif //SHEEP_GOES_DEVILE_ENTITY_STORAGE_H
