//
// Created by Kamil on 05.07.2026.
//

#ifndef SHEEP_GOES_DEVILE_EDITOR_UNDO_REDO_HPP
#define SHEEP_GOES_DEVILE_EDITOR_UNDO_REDO_HPP
#include <any>

#include "AssetManager.h"
#include "EntitySelection.h"
#include "Components.h"
#include "EntityStorage.hpp"
#include "UndoRedo.hpp"

struct UndoRedoContext
{
    EntityStorage& Storage;
    EntitySelection& Selection;
    AssetManager& Assets;
};

struct SelectionPayload
{
    UUID OldSelection;
    UUID NewSelection;
};

template<typename T>
struct AddComponentPayload
{
    UUID TargetEntity;
};

template<typename T>
struct ChangeComponentPayload
{
    UUID TargetEntity;
    T OldState;
    T NewState;
};

template<typename T>
struct RemoveComponentPayload
{
    UUID TargetEntity;
    T Component;
};

struct CreateEntityPayload
{
    UUID TargetEntity;
};

struct RemoveEntityPayload
{
    UUID TargetEntity;
    std::vector<std::any> Components;
};

struct CopyEntityPayload : RemoveEntityPayload
{
};

struct SwapEntityPayload
{
    UUID A;
    UUID B;
};

template<typename T>
struct AddTagPayload
{
    UUID TargetEntity;
};

template<typename T>
struct RemoveTagPayload
{
    UUID TargetEntity;
};

struct ChangeScenePayload
{
    UUID From;
    UUID To;
};

struct CreateScenePayload
{
    UUID PreviousScene;
};

struct ChangeSceneNamePayload
{
    std::string NewName;
    std::string OldName;
};

struct UndoRedoResolver
{
    void CreateEntityWithComponents(const RemoveEntityPayload* payload, UndoRedoContext& ctx) const
    {
        entt::registry& storage = ctx.Storage.Registry;
        const entt::entity entity = storage.create();
        for (const auto& component : payload->Components)
        {
#define X(e, t) \
if (auto* compVal = std::any_cast<t>(&component)) \
{ \
storage.emplace<t>(entity, *compVal); \
continue; \
}
            AllComponentNamesMacro(X);
#undef X

#define X(e, t) \
if (std::any_cast<t>(&component)) \
{ \
storage.emplace<t>(entity); \
continue; \
}
            TagComponentNamesMacro(X);
#undef X
        }
        ctx.Storage.AddEntity(payload->TargetEntity, entity);
    }

    void Undo(const std::any& data, UndoRedoContext& ctx) const
    {
        entt::registry& storage = ctx.Storage.Registry;
        if (auto* payload = std::any_cast<SelectionPayload>(&data))
        {
            ctx.Selection.SelectedEntity = payload->OldSelection;
            return;
        }

#define X(e, t) if (auto* payload = std::any_cast<ChangeComponentPayload<t>>(&data)) { \
storage.replace<t>(ctx.Storage.GetEntity(payload->TargetEntity), payload->OldState); \
return; \
}
        AllComponentNamesMacro(X)
#undef X

#define X(e, t) if (auto* payload = std::any_cast<AddComponentPayload<t>>(&data)) { \
storage.remove<t>(ctx.Storage.GetEntity(payload->TargetEntity)); \
return; \
}
        AdditionalComponentNamesMacro(X)
#undef X

#define X(e, t) if (auto* payload = std::any_cast<RemoveComponentPayload<t>>(&data)) { \
storage.emplace<t>(ctx.Storage.GetEntity(payload->TargetEntity), payload->Component); \
return; \
}
        AdditionalComponentNamesMacro(X)
#undef X

#define X(e, t) if (auto* payload = std::any_cast<AddTagPayload<t>>(&data)) { \
storage.remove<t>(ctx.Storage.GetEntity(payload->TargetEntity)); \
return; \
}
        TagComponentNamesMacro(X)
#undef X

#define X(e, t) if (auto* payload = std::any_cast<RemoveTagPayload<t>>(&data)) { \
storage.emplace<t>(ctx.Storage.GetEntity(payload->TargetEntity)); \
return; \
}
        TagComponentNamesMacro(X)
#undef X

        if (auto* payload = std::any_cast<CreateEntityPayload>(&data))
        {
            ctx.Storage.DestroyEntity(payload->TargetEntity);
            return;
        }

        if (auto* payload = std::any_cast<RemoveEntityPayload>(&data))
        {
            CreateEntityWithComponents(payload, ctx);
            ctx.Selection.SelectedEntity = payload->TargetEntity;
            return;
        }

        if (auto* payload = std::any_cast<SwapEntityPayload>(&data))
        {
            const entt::entity eA = ctx.Storage.GetEntity(payload->A);
            const entt::entity eB = ctx.Storage.GetEntity(payload->B);
            std::swap(storage.get<OrderComponent>(eA).Value, storage.get<OrderComponent>(eB).Value);
            return;
        }

        if (auto* payload = std::any_cast<CopyEntityPayload>(&data))
        {
            ctx.Storage.DestroyEntity(payload->TargetEntity);
            return;
        }

        if (auto* payload = std::any_cast<ChangeScenePayload>(&data))
        {
            ctx.Assets.Levels.Load(payload->From);
            return;
        }

        if (std::any_cast<CreateScenePayload>(&data))
        {
            ctx.Assets.Levels.Delete();
            return;
        }

        if (auto* payload = std::any_cast<ChangeSceneNamePayload>(&data))
        {
            ctx.Assets.Levels.Rename(payload->OldName);
            return;
        }
    }

    void Redo(const std::any& data, UndoRedoContext& ctx) const
    {
        entt::registry& storage = ctx.Storage.Registry;
        if (auto* payload = std::any_cast<SelectionPayload>(&data))
        {
            ctx.Selection.SelectedEntity = payload->NewSelection;
            return;
        }

#define X(e, t) if (auto* payload = std::any_cast<ChangeComponentPayload<t>>(&data)) \
    { \
        storage.replace<t>(ctx.Storage.GetEntity(payload->TargetEntity), payload->NewState); \
        return; \
    }
        AdditionalComponentNamesMacro(X)
#undef X

#define X(e, t) if (auto* payload = std::any_cast<AddComponentPayload<t>>(&data)) { \
            storage.emplace<t>(ctx.Storage.GetEntity(payload->TargetEntity)); \
            return; \
        }
        AdditionalComponentNamesMacro(X)
#undef X

#define X(e, t) if (auto* payload = std::any_cast<RemoveComponentPayload<t>>(&data)) { \
            storage.remove<t>(ctx.Storage.GetEntity(payload->TargetEntity)); \
            return; \
        }
        AdditionalComponentNamesMacro(X)
#undef X

#define X(e, t) if (auto* payload = std::any_cast<AddTagPayload<t>>(&data)) { \
            storage.emplace<t>(ctx.Storage.GetEntity(payload->TargetEntity)); \
            return; \
        }
        TagComponentNamesMacro(X)
#undef X

#define X(e, t) if (auto* payload = std::any_cast<RemoveTagPayload<t>>(&data)) { \
            storage.remove<t>(ctx.Storage.GetEntity(payload->TargetEntity)); \
            return; \
        }
        TagComponentNamesMacro(X)
#undef X

        if (auto* payload = std::any_cast<CreateEntityPayload>(&data))
        {
            ctx.Storage.CreateEntity(payload->TargetEntity);
            return;
        }

        if (const auto* payload = std::any_cast<RemoveEntityPayload>(&data))
        {
            ctx.Storage.DestroyEntity(payload->TargetEntity);
            return;
        }

        if (auto* payload = std::any_cast<SwapEntityPayload>(&data))
        {
            const entt::entity eA = ctx.Storage.GetEntity(payload->A);
            const entt::entity eB = ctx.Storage.GetEntity(payload->B);
            std::swap(storage.get<OrderComponent>(eA).Value, storage.get<OrderComponent>(eB).Value);
            return;
        }

        if (auto* payload = std::any_cast<CopyEntityPayload>(&data))
        {
            CreateEntityWithComponents(payload, ctx);
            ctx.Selection.SelectedEntity = payload->TargetEntity;
            return;
        }

        if (auto* payload = std::any_cast<ChangeScenePayload>(&data))
        {
            ctx.Assets.Levels.Load(payload->To);
            return;
        }

        if (std::any_cast<CreateScenePayload>(&data))
        {
            ctx.Assets.Levels.Create();
            return;
        }

        if (auto* payload = std::any_cast<ChangeSceneNamePayload>(&data))
        {
            ctx.Assets.Levels.Rename(payload->NewName);
            return;
        }
    }
};

struct EditorUndoRedo : UndoRedo<UndoRedoResolver, UndoRedoContext>
{
};

#endif //SHEEP_GOES_DEVILE_EDITOR_UNDO_REDO_HPP
