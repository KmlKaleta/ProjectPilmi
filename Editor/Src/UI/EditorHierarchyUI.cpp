//
// Created by Kamil on 16.06.2026.
//
#include "EditorHierarchyUI.h"
#include "AssetManager.h"
#include "imgui.h"
#include "../EntitySelection.h"
#include "../EditorHierarchy.h"
#include "../EditorUndoRedo.hpp"
#include "../UndoRecorder.hpp"

void EditorHierarchyUI::Draw(EditorHierarchy& hierarchy, EntitySelection& selection, AssetManager& assetManager,
                             EditorUndoRedo& undoRedo) const
{
    ImGui::Begin("Hierarchy");

    EntityStorage& storage = assetManager.Levels.CurrentLevel().Entities;
    const auto selectedEntity = storage.GetEntity(selection.SelectedEntity);

    if (ImGui::Button("Add"))
    {
        RecordEntityCreation(undoRedo, storage, assetManager.UUIDFactory);
    }

    ImGui::SameLine();

    if (ImGui::Button("Delete") && selection.SelectedEntity != 0)
    {
        RecordEntityDeletion(undoRedo, storage, selection);
    }

    ImGui::SameLine();

    if (ImGui::Button("Copy") && selection.SelectedEntity != 0)
    {
        RecordEntityCopy(undoRedo, storage, assetManager.UUIDFactory, selectedEntity);
    }

    ImGui::Separator();

    const auto view = storage.Registry.view<const TagComponent, OrderComponent>(
        entt::exclude<EntityGroupChildComponent>);

    hierarchy.Order.assign(storage.EntityMap.begin(), storage.EntityMap.end());

    std::sort(hierarchy.Order.begin(), hierarchy.Order.end(), [&](const auto& a, const auto& b)
    {
        return view.get<OrderComponent>(std::get<1>(a)).Value < view.get<OrderComponent>(std::get<1>(b)).Value;
    });

    ImGui::BeginChild("hierarchy_child");

    for (const auto& entityId : hierarchy.Order)
    {
        const auto& [id, entity] = entityId;
        const auto& [Tag] = view.get<TagComponent>(entity);
        auto& [Order] = view.get<OrderComponent>(entity);

        ImGui::PushID(static_cast<int>(entity));

        if (ImGui::Selectable(("##" + Tag).c_str(), id == selection.SelectedEntity, ImGuiSelectableFlags_AllowOverlap))
        {
            RecordEntitySelection(undoRedo, selection, id);
        }


        const char* name = Tag.c_str();
        if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
        {
            // Set payload to carry the index of our item (could be anything)
            ImGui::SetDragDropPayload("hierarchy_drag", &id, sizeof(UUID));
            // Display preview (could be anything, e.g. when dragging an image we could decide to display
            // the filename and a small preview of the image, etc.)
            ImGui::Text(name);
            ImGui::EndDragDropSource();
        }

        if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("hierarchy_drag"))
            {
                assert(payload->DataSize == sizeof(UUID));
                const UUID draggedEntity = *static_cast<const UUID *>(payload->Data);
                std::swap(Order, view.get<OrderComponent>(storage.GetEntity(draggedEntity)).Value);
                undoRedo.AddAction(SwapEntityPayload{id, draggedEntity});
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
