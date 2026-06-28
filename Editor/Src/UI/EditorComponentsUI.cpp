//
// Created by Kamil on 16.06.2026.
//
#include "EditorComponentsUI.h"
#include "AssetManager.h"
#include "../EntitySelection.h"
#include "imgui.h"
#include "Fields/Range.hpp"
#include "misc/cpp/imgui_stdlib.h"
#include "ImGuiExtensions.h"
#include "StringUtility.hpp"
#include "VisitedComponents.h"

void EditorComponentsUI::Draw(const EntitySelection& selection, AssetManager& assetManager) const
{
    ImGui::Begin("Components");
    if (selection.SelectedEntity == entt::null)
    {
        ImGui::Text("No Entity Selected");
        return ImGui::End();
    }

    EntityStorage& storage = assetManager.Levels.CurrentLevel().Entities;
    const UUID id = storage.Registry.get<IDComponent>(selection.SelectedEntity).Value;
    ImGui::Text("%llu", id.Value);

    bool additionalComponentsMatrix[static_cast<int>(AdditionalComponentType::COUNT)];
    bool tagComponentsMatrix[static_cast<int>(TagComponentType::COUNT)];

    auto& [Tag] = storage.Registry.get<TagComponent>(selection.SelectedEntity);
    std::string componentName = Tag;
    ImGui::InputText("##", &componentName);
    if (ImGui::IsItemDeactivatedAfterEdit() && !IsNullOrWhiteSpace(componentName))
    {
        Tag = componentName;
    }

    size_t ai = 0;
    size_t ti = 0;

    auto ResolveComponent = [&](const char* fieldName, auto& component)
    {
        std::string s(fieldName);
        s += "##";
        s += fieldName;

        const char* name = s.c_str();

        using type = std::decay_t<decltype(component)>;
        if constexpr (std::is_same_v<type, float>)
        {
            ImGui::InputFloat(name, &component, 0.01f, 0.02f, "%.2f");
        } else if constexpr (std::is_same_v<type, bool>)
        {
            ImGui::Checkbox(name, &component);
        } else if constexpr (std::is_same_v<type, int>)
        {
            ImGui::InputInt(name, &component);
        } else if constexpr (std::is_same_v<type, std::string>)
        {
            ImGui::InputText(name, &component);
        } else if constexpr (std::is_same_v<type, Range<float>>)
        {
            float x = component.Get();
            ImGui::SliderFloat(name, &x, component.Min, component.Max, "%.2f");
            component.Set(x);
        } else if constexpr (std::is_same_v<type, Range<int>>)
        {
            int x = component.Get();
            ImGui::SliderInt(name, &x, component.Min, component.Max, "%d");
            component.Set(x);
        } else if constexpr (std::is_same_v<type, size_t> || std::is_same_v<type, uint32_t>)
        {
            ImGui::InputScalar(name, ImGuiDataType_U32, &component);
        } else if constexpr (std::is_same_v<type, Renderer>)
        {
            ImGui::RendererEdit(fieldName, &component, assetManager.Sprites);
        } else if constexpr (std::is_same_v<type, Vector2>)
        {
            ImGui::DragFloat2(name, &component.x, 0.01f);
        } else if constexpr (std::is_same_v<type, WorldPosition>)
        {
            ImGui::WorldPositionEdit(name, &component);
        } else
        {
            ImGui::Text("%s field type has unsupported type %s", name, typeid(type).name());
        }
    };

#define X(e, t) bool has##e##Component = tagComponentsMatrix[ti++] = storage.Registry.all_of<t>(selection.SelectedEntity); \
    if (has##e##Component) \
    { \
        ImGui::PushID(ti + ai); \
        if (ImGui::Button("X##X")) { \
            storage.Registry.remove<t>(selection.SelectedEntity); \
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

#define X(e, t) t * e##Component = storage.Registry.try_get<t>(selection.SelectedEntity); \
    bool has##e##Component = additionalComponentsMatrix[ai++] = e##Component; \
    if (has##e##Component) \
    { \
        ImGui::PushID(ti + ai); \
        if (ImGui::Button("X##X")) { \
            storage.Registry.remove<t>(selection.SelectedEntity); \
            additionalComponentsMatrix[ai - 1] = false; \
        } \
        ImGui::SameLine(); \
        if (ImGui::CollapsingHeader(#t, ImGuiTreeNodeFlags_DefaultOpen)) \
        { \
            ImGui::Indent(); \
            visit_struct::for_each(*e##Component, ResolveComponent); \
            ImGui::Unindent(); \
        } \
        ImGui::PopID(); \
    }
    AdditionalComponentNamesMacro(X)
#undef X


#define X(e, t) t * e##Component = storage.Registry.try_get<t>(selection.SelectedEntity); \
    if (e##Component && ImGui::CollapsingHeader(#t)) \
    { \
        ImGui::BeginDisabled(); \
        ImGui::Indent(); \
        visit_struct::for_each(*e##Component, ResolveComponent); \
        ImGui::Unindent(); \
        ImGui::EndDisabled(); \
    }
    UtilityComponentNamesMacro(X)
#undef X


    ImGui::Spacing();
    ImGui::Separator();

    if (ImGui::Button("Add Component"))
    {
        ImGui::OpenPopup("add_component");
    }

    ai = 0;
    ti = 0;

    if (ImGui::BeginPopup("add_component"))
    {
#define X(e, t) if (!additionalComponentsMatrix[ai++] && ImGui::MenuItem(#t)) \
            storage.Registry.emplace<t>(selection.SelectedEntity);
        AdditionalComponentNamesMacro(X)
#undef X

#define X(e, t)if (!tagComponentsMatrix[ti++] && ImGui::MenuItem(#t)) \
            storage.Registry.emplace<t>(selection.SelectedEntity);
        TagComponentNamesMacro(X)
#undef X

        ImGui::EndPopup();
    }

    ImGui::End();
}
