//
// Created by Kamil on 16.06.2026.
//
#include "EditorHierarchyUI.h"
#include "AssetManager.h"
#include "imgui.h"
#include "../EntitySelection.h"
#include "../EditorHierarchy.h"


void EditorHierarchyUI::Draw(EditorHierarchy& hierarchy, EntitySelection& selection, AssetManager& assetManager) const
{
    ImGui::Begin("Hierarchy");

    EntityStorage& storage = assetManager.Levels.CurrentLevel().Entities;

    if (ImGui::Button("Add"))
    {
        const auto entity = storage.CreateEntity(assetManager.UUIDFactory);
        storage.Registry.get<TagComponent>(entity).Value = "Entity";
    }

    ImGui::SameLine();

    if (ImGui::Button("Delete") && selection.SelectedEntity != entt::null)
    {
        storage.Registry.destroy(selection.SelectedEntity);
        selection.SelectedEntity = entt::null;
    }

    ImGui::SameLine();

    if (ImGui::Button("Copy") && selection.SelectedEntity != entt::null)
    {
        entt::entity copied = storage.CreateEntity(assetManager.UUIDFactory);
        storage.Registry.get<TagComponent>(copied).Value = storage.Registry.get<TagComponent>(selection.SelectedEntity).
                Value;

        const uint32_t order = storage.Registry.get<OrderComponent>(selection.SelectedEntity).Value + 1;
        for (const auto e : storage.Registry.view<OrderComponent>())
        {
            if (auto& orderComponent = storage.Registry.get<OrderComponent>(e); orderComponent.Value >= order)
            {
                orderComponent.Value++;
            }
        }

        storage.Registry.get<OrderComponent>(copied).Value = order;

#define X(e, t) if (t * component = storage.Registry.try_get<t>(selection.SelectedEntity)) \
        { \
            storage.Registry.emplace<t>(copied, *component); \
        }
        AdditionalComponentNamesMacro(X)
#undef X

#define X(e, t) if (storage.Registry.all_of<t>(selection.SelectedEntity)) \
        { \
            storage.Registry.emplace<t>(copied); \
        }
        TagComponentNamesMacro(X)
#undef X
    }

    ImGui::Separator();

    const auto view = storage.Registry.view<const TagComponent, OrderComponent>(
        entt::exclude<EntityGroupChildComponent>);
    hierarchy.Order.assign(view.begin(), view.end());

    std::sort(hierarchy.Order.begin(), hierarchy.Order.end(), [&](const auto& a, const auto& b)
    {
        return view.get<OrderComponent>(a).Value < view.get<OrderComponent>(b).Value;
    });

    ImGui::BeginChild("hierarchy_child");

    for (auto entity : hierarchy.Order)
    {
        const auto& [Tag] = view.get<TagComponent>(entity);
        auto& [Order] = view.get<OrderComponent>(entity);

        ImGui::PushID(static_cast<int>(entity));

        if (ImGui::Selectable(("##" + Tag).c_str(), entity == selection.SelectedEntity,
                              ImGuiSelectableFlags_AllowOverlap))
        {
            selection.SelectedEntity = entity;
        }


        const char* name = Tag.c_str();
        if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
        {
            // Set payload to carry the index of our item (could be anything)
            ImGui::SetDragDropPayload("hierarchy_drag", &entity, sizeof(entt::entity));
            // Display preview (could be anything, e.g. when dragging an image we could decide to display
            // the filename and a small preview of the image, etc.)
            ImGui::Text(name);
            ImGui::EndDragDropSource();
        }

        if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("hierarchy_drag"))
            {
                assert(payload->DataSize == sizeof(entity));
                const entt::entity draggedEntity = *static_cast<const entt::entity *>(payload->Data);
                std::swap(Order, view.get<OrderComponent>(draggedEntity).Value);
            }
            ImGui::EndDragDropTarget();
        }

        ImGui::SameLine();

        if (const EntityGroupComponent* group = storage.Registry.try_get<EntityGroupComponent>(entity))
        {
            if (ImGui::CollapsingHeader(name))
            {
            }
        } else
        {
            ImGui::Text("%s", name);
        }

        ImGui::PopID();
    }

    ImGui::EndChild();

    ImGui::End();
}
