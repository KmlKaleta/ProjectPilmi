//
// Created by Kamil on 16.06.2026.
//
#include "EditorComponentsUI.h"
#include "Components.h"
#include "AssetManager.h"
#include "../EntitySelection.h"
#include "imgui.h"
#include "Fields/Range.hpp"
#include "include/visit_struct/visit_struct.hpp"
#include "misc/cpp/imgui_stdlib.h"

VISITABLE_STRUCT(ParallaxComponent, Strength);
VISITABLE_STRUCT(EntityGroupComponent, Entities);
VISITABLE_STRUCT(EntityGroupChildComponent, Value);
VISITABLE_STRUCT(OrderComponent, Value);

bool IsNullOrWhiteSpace(const std::string& s)
{
    return s.empty() ||
           std::all_of(s.begin(), s.end(),
                       [](const unsigned char c)
                       {
                           return std::isspace(c);
                       });
}

// bool IsDuplicated(const std::string& name,
//                   entt::basic_view<entt::get_t<const entt::basic_sigh_mixin<entt::basic_storage<TagComponent>,
//                       entt::basic_registry<>>>, entt::exclude_t<>> view)
// {
//     for (auto [entity, tag] : view.each())
//     {
//         if (tag.Value == name)
//             return true;
//     }
//     return false;
// }
//
// void Rename(TagComponent& tagComponent, const std::string& name, const AssetManager& assetManager)
// {
//     if (tagComponent.Value == name || IsNullOrWhiteSpace(name))
//         return;
//
//     std::string nameToSet = name;
//     if (const auto view = assetManager.Levels.Entities.Registry.view<TagComponent>(); IsDuplicated(name, view))
//     {
//         for (size_t i = 1; ; i++)
//         {
//             if (const std::string newName = name + " (" + std::to_string(i) + ")"; !IsDuplicated(newName, view))
//             {
//                 nameToSet = newName;
//                 break;
//             }
//         }
//     }
//
//     tagComponent.Value = nameToSet;
// }

void EditorComponentsUI::Draw(const EntitySelection& selection, AssetManager& assetManager) const
{
    ImGui::Begin("Components");
    if (selection.SelectedEntity == entt::null)
    {
        ImGui::Text("No Entity Selected");
        return ImGui::End();
    }

    const UUID id = assetManager.Levels.Entities.Registry.get<IDComponent>(selection.SelectedEntity).Value;
    ImGui::Text("%llu", id.Value);

    bool componentsMatrix[static_cast<int>(AdditionalComponentType::COUNT)];

    auto& [Tag] = assetManager.Levels.Entities.Registry.get<TagComponent>(selection.SelectedEntity);
    std::string componentName = Tag;
    ImGui::InputText("##", &componentName);
    if (ImGui::IsItemDeactivatedAfterEdit() && !IsNullOrWhiteSpace(componentName))
    {
        Tag = componentName;
    }

    size_t i = 0;

    auto ResolveComponent = [](const char* name, auto& component)
    {
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
        } else if constexpr (std::is_same_v<type, size_t>)
        {
            if constexpr (sizeof(size_t) == 8)
            {
                ImGui::InputScalar(name, ImGuiDataType_U64, &component);
            }
            else
            {
                ImGui::InputScalar(name, ImGuiDataType_U32, &component);
            }
        } else if constexpr (std::is_same_v<type, uint32_t>)
        {
            ImGui::InputScalar(name, ImGuiDataType_U32, &component);
        } else
        {
            ImGui::Text("%s field type has unsupported type %s", name, typeid(type).name());
        }
    };

    ImGui::Separator();
    ImGui::Spacing();

#define X(e, t) t * e##Component = assetManager.Levels.Entities.Registry.try_get<t>(selection.SelectedEntity); \
    bool has##e##Component = componentsMatrix[i++] = e##Component; \
    if (has##e##Component && ImGui::CollapsingHeader(#t)) \
    { \
        visit_struct::for_each(*e##Component, ResolveComponent); \
    }
    AdditionalComponentNamesMacro(X)
#undef X


#define X(e, t) t * e##Component = assetManager.Levels.Entities.Registry.try_get<t>(selection.SelectedEntity); \
    if (e##Component && ImGui::CollapsingHeader(#t)) \
    { \
        ImGui::BeginDisabled(); \
        visit_struct::for_each(*e##Component, ResolveComponent); \
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

    i = 0;
    if (ImGui::BeginPopup("add_component"))
    {
#define X(e, t) if (!componentsMatrix[i++] && ImGui::MenuItem(#t)) \
            assetManager.Levels.Entities.Registry.emplace<t>(selection.SelectedEntity);
        AdditionalComponentNamesMacro(X)
#undef X

        ImGui::EndPopup();
    }

    ImGui::End();
}
