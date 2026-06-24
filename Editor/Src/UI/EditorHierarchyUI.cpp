//
// Created by Kamil on 16.06.2026.
//
#include "EditorHierarchyUI.h"
#include "AssetManager.h"
#include "imgui.h"
#include "../EntitySelection.h"


void EditorHierarchyUI::Draw(EditorHierarchy& hierarchy, EntitySelection& selection, AssetManager& assetManager) const
{
    ImGui::Begin("Hierarchy");
    if (ImGui::Button("Add Entity"))
    {
        const auto entity = assetManager.Levels.Entities.CreateEntity(assetManager.UUIDFactory);
        assetManager.Levels.Entities.Registry.get<TagComponent>(entity).Value = "Entity";
    }

    ImGui::SameLine();

    if (ImGui::Button("Delete Entity"))
    {
        assetManager.Levels.Entities.Registry.destroy(selection.SelectedEntity);
    }

    ImGui::Separator();

    const auto view = assetManager.Levels.Entities.Registry.view<const TagComponent, OrderComponent>(
        entt::exclude<EntityGroupChildComponent>);
    std::vector order(view.begin(), view.end());

    std::sort(order.begin(), order.end(), [&](const auto& a, const auto& b)
    {
        return view.get<OrderComponent>(a).Value < view.get<OrderComponent>(b).Value;
    });

    for (auto entity : order)
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

        if (const EntityGroupComponent* group = assetManager.Levels.Entities.Registry.try_get<
            EntityGroupComponent>(entity))
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

    ImGui::End();
}
