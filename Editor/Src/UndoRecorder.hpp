//
// Created by Kamil on 07.07.2026.
//

#ifndef SHEEP_GOES_DEVILE_UNDO_RECORDER_H
#define SHEEP_GOES_DEVILE_UNDO_RECORDER_H
#include "EditorUndoRedo.hpp"

template<typename T>
void RecordTagAdd(EditorUndoRedo& undoRedo, entt::registry& storage, const entt::entity entity, const UUID id)
{
    storage.emplace<T>(entity);
    undoRedo.AddAction(AddTagPayload<T>{id});
}

template<typename T>
void RecordComponentAdd(EditorUndoRedo& undoRedo, entt::registry& storage, const entt::entity entity, const UUID id)
{
    storage.emplace<T>(entity);
    undoRedo.AddAction(AddComponentPayload<T>{id});
}

template<typename T>
void RecordTagRemove(EditorUndoRedo& undoRedo, entt::registry& storage, const entt::entity entity, const UUID id)
{
    undoRedo.AddAction(RemoveTagPayload<T>{id});
    storage.remove<T>(entity);
}

template<typename T>
void RecordComponentRemove(EditorUndoRedo& undoRedo, entt::registry& storage, const entt::entity entity, const UUID id,
                           const T& component)
{
    undoRedo.AddAction(RemoveComponentPayload<T>{id, component});
    storage.remove<T>(entity);
}

inline void RecordEntityCreation(EditorUndoRedo& undoRedo, EntityStorage& storage, UUIDFactory& factory)
{
    const UUID id = factory.Get();
    const auto entity = storage.CreateEntity(id);
    storage.Registry.get<TagComponent>(entity).Value = "Entity";
    const CreateEntityPayload payload{id};
    undoRedo.AddAction(payload);
}

inline RemoveEntityPayload GetRemoveEntityPayload(entt::registry& registry, const UUID id, const entt::entity entity)
{
    RemoveEntityPayload payload{id};
    for (auto&& [_, sparse] : registry.storage())
    {
        if (!sparse.contains(entity))
        {
            continue;
        }
        entt::type_info type_id = sparse.info();

#define X(e, t) \
if (type_id == entt::type_id<t>()) \
{ \
const t & comp = registry.get<t>(entity); \
payload.Components.emplace_back(comp); \
continue; \
}

        AllComponentNamesMacro(X)
#undef X

#define X(e, t) \
if (type_id == entt::type_id<t>()) \
{ \
payload.Components.emplace_back(t{}); \
continue; \
}

        TagComponentNamesMacro(X)
#undef X
    }

    return payload;
}

inline void RecordEntityDeletion(EditorUndoRedo& undoRedo, EntityStorage& storage, EntitySelection& selection)
{
    const RemoveEntityPayload payload = GetRemoveEntityPayload(storage.Registry, selection.SelectedEntity,
                                                               storage.GetEntity(selection.SelectedEntity));
    undoRedo.AddAction(payload);
    storage.DestroyEntity(selection.SelectedEntity);
    selection.SelectedEntity = 0;
}

inline void RecordEntityCopy(EditorUndoRedo& undoRedo, EntityStorage& storage, UUIDFactory& factory,
                             const entt::entity entityToCopy)
{
    const UUID id = factory.Get();
    const entt::entity copied = storage.CreateEntity(id);
    storage.Registry.get<TagComponent>(copied).Value = storage.Registry.get<TagComponent>(entityToCopy).
            Value;

    const uint32_t order = storage.Registry.get<OrderComponent>(entityToCopy).Value + 1;
    for (const auto e : storage.Registry.view<OrderComponent>())
    {
        if (auto& orderComponent = storage.Registry.get<OrderComponent>(e); orderComponent.Value >= order)
        {
            orderComponent.Value++;
        }
    }

    storage.Registry.get<OrderComponent>(copied).Value = order;

#define X(e, t) if (t * component = storage.Registry.try_get<t>(entityToCopy)) \
{ \
storage.Registry.emplace<t>(copied, *component); \
}
    AdditionalComponentNamesMacro(X)
#undef X

#define X(e, t) if (storage.Registry.all_of<t>(entityToCopy)) \
{ \
storage.Registry.emplace<t>(copied); \
}
    TagComponentNamesMacro(X)
#undef X

    const auto payload = CopyEntityPayload{GetRemoveEntityPayload(storage.Registry, id, copied)};
    undoRedo.AddAction(payload);
}

inline void RecordEntitySelection(EditorUndoRedo& undoRedo, EntitySelection& selection, const UUID id)
{
    SelectionPayload payload{selection.SelectedEntity, id};
    selection.SelectedEntity = id;
    undoRedo.AddAction(payload);
}

inline void RecordSceneChange(EditorUndoRedo& undoRedo, LevelManager& levelManager, UUID scene)
{
    ChangeScenePayload payload{levelManager.CurrentLevelId, scene};
    levelManager.Load(scene);
    undoRedo.AddAction(payload);
}

inline void RecordSceneCreation(EditorUndoRedo& undoRedo, LevelManager& levelManager)
{
    CreateScenePayload payload{levelManager.CurrentLevelId};
    levelManager.Create();
    undoRedo.AddAction(payload);
}

inline void RecordChangeSceneName(EditorUndoRedo& undoRedo, LevelManager& levelManager, const std::string& name)
{
    levelManager.Rename(name);
    const ChangeSceneNamePayload payload{levelManager.Metadata[levelManager.Ids[levelManager.CurrentLevelId]], name};
    undoRedo.AddAction(payload);
}

#endif //SHEEP_GOES_DEVILE_UNDO_RECORDER_H
