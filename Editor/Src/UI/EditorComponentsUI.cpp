//
// Created by Kamil on 16.06.2026.
//
#include "EditorComponentsUI.h"
#include "AssetManager.h"
#include "../EntitySelection.h"
#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"
#include "StringUtility.hpp"
#include "../../../EditorDependency/Src/VisitedComponents.h"
#include "glm/detail/func_packing_simd.inl"
#include "../EditorUndoRedo.hpp"
#include "../UndoRecorder.hpp"
#include "ResolveComponent.hpp"

template<typename T>
void OnAdd(T& component, entt::entity entity, entt::registry& registry, const AssetManager& assetManager,
           EditorUndoRedo& undoRedo)
{
}

template<>
void OnAdd<PhysicsBoxComponent>(PhysicsBoxComponent& component, const entt::entity entity, entt::registry& registry,
                                const AssetManager& assetManager, EditorUndoRedo& undoRedo)
{
    if (const RendererComponent* renderer = registry.try_get<RendererComponent>(entity))
    {
        component = {assetManager.Sprites.FromId(renderer->Data.Sprite).DefaultCollider};
    }
}

void EditorComponentsUI::Draw(const EntitySelection& selection, AssetManager& assetManager,
                              EditorUndoRedo& undoRedo) const
{
    ImGui::Begin("Components");
    if (selection.SelectedEntity == 0)
    {
        ImGui::Text("No Entity Selected");
        return ImGui::End();
    }

    EntityStorage& storage = assetManager.Levels.CurrentLevel().Entities;
    ImGui::Text("%llu", selection.SelectedEntity.Value);

    bool additionalComponentsMatrix[static_cast<int>(AdditionalComponentType::COUNT)];
    bool tagComponentsMatrix[static_cast<int>(TagComponentType::COUNT)];

    const float footer_height_to_reserve = ImGui::GetFrameHeightWithSpacing();
    const entt::entity selectedEntity = storage.GetEntity(selection.SelectedEntity);
    size_t ai = 0;
    size_t ti = 0;

    if (ImGui::BeginChild("component_child", ImVec2(0, -footer_height_to_reserve), ImGuiChildFlags_None))
    {
        auto& [Tag] = storage.Registry.get<TagComponent>(selectedEntity);
        std::string componentName = Tag;
        ImGui::InputText("##", &componentName);
        if (ImGui::IsItemDeactivatedAfterEdit() && !IsNullOrWhiteSpace(componentName))
        {
            Tag = componentName;
        }

#define X(e, t) bool has##e##Component = tagComponentsMatrix[ti++] = storage.Registry.all_of<t>(selectedEntity); \
if (has##e##Component) \
{ \
ImGui::PushID(ti + ai); \
if (ImGui::Button("X##X")) { \
RecordTagRemove<t>(undoRedo, storage.Registry, selectedEntity, selection.SelectedEntity); \
tagComponentsMatrix[ti - 1] = false; \
} \
ImGui::PopID(); \
ImGui::SameLine(); \
ImGui::Text(#t); \
}
        TagComponentNamesMacro(X)
#undef X

        ImGui::Separator();
        ImGui::Spacing();

#define X(e, t) t * e##Component = storage.Registry.try_get<t>(selectedEntity); \
bool has##e##Component = additionalComponentsMatrix[ai++] = e##Component; \
if (has##e##Component) \
{ \
ImGui::PushID(ti + ai); \
if (ImGui::Button("X##X")) { \
RecordComponentRemove<t>(undoRedo, storage.Registry, selectedEntity, selection.SelectedEntity, *e##Component); \
additionalComponentsMatrix[ai - 1] = false; \
} \
ImGui::SameLine(); \
if (ImGui::CollapsingHeader(#t, ImGuiTreeNodeFlags_DefaultOpen)) \
{ \
ImGui::Indent(); \
static t oldState; \
static UUID lastEntity = 0; \
if (lastEntity != selection.SelectedEntity) \
{ \
oldState = *e##Component; \
lastEntity = selection.SelectedEntity; \
} \
bool componentChangedInThisFrame = false; \
visit_struct::for_each(*e##Component, [&](const char* name, auto& value) { componentChangedInThisFrame = ResolveComponent(name, value, assetManager); }); \
if (componentChangedInThisFrame) \
{ \
undoRedo.AddAction(ChangeComponentPayload<t>{selection.SelectedEntity, oldState, *e##Component}); \
oldState = *e##Component; \
} \
ImGui::Unindent(); \
} \
ImGui::PopID(); \
}
        AdditionalComponentNamesMacro(X)
#undef X


#define X(e, t) t * e##Component = storage.Registry.try_get<t>(selectedEntity); \
        if (e##Component && ImGui::CollapsingHeader(#t)) \
        { \
        ImGui::BeginDisabled(); \
        ImGui::Indent(); \
        visit_struct::for_each(*e##Component, [&](const char* name, auto& value) { ResolveComponent(name, value, assetManager); }); \
        ImGui::Unindent(); \
        ImGui::EndDisabled(); \
        }
        UtilityComponentNamesMacro(X)
#undef X
    }
    ImGui::EndChild();
    ImGui::Separator();

    if (ImGui::Button("Add Component"))
    {
        ImGui::OpenPopup("add_component");
    }

    ai = 0;
    ti = 0;

    if (ImGui::BeginPopup("add_component"))
    {
#define X(e, t) \
if (!additionalComponentsMatrix[ai++] && ImGui::MenuItem(#t)) \
{ \
t comp{}; \
OnAdd(comp, selectedEntity, storage.Registry, assetManager, undoRedo); \
RecordComponentAdd(undoRedo, comp, storage.Registry, selectedEntity, selection.SelectedEntity); \
    }
    AdditionalComponentNamesMacro(X)
#undef X

#define X(e, t) \
    if (!tagComponentsMatrix[ti++] && ImGui::MenuItem(#t)) \
    { \
        RecordTagAdd<t>(undoRedo, storage.Registry, selectedEntity, selection.SelectedEntity); \
    }
                TagComponentNamesMacro(X)
#undef X

                ImGui::EndPopup();
            }

            ImGui::End();
        }
