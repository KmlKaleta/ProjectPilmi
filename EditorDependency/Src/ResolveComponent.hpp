//
// Created by Kamil on 07.07.2026.
//

#ifndef SHEEP_GOES_DEVILE_RESOLVE_COMPONENT_HPP
#define SHEEP_GOES_DEVILE_RESOLVE_COMPONENT_HPP
#include "AssetManager.h"
#include "imgui.h"
#include "include/visit_struct/visit_struct.hpp"

template<typename T>
bool ResolveComponent(const char* fieldName, T& component, AssetManager& assetManager, size_t i = 0)
{
    std::string s(fieldName);
    s += "##";
    s += fieldName;

    const char* label = s.c_str();

    using type = std::decay_t<decltype(component)>;
    if constexpr (std::is_same_v<type, float>)
    {
        ImGui::InputFloat(label, &component, 0.01f, 0.02f, "%.2f");
    } else if constexpr (std::is_same_v<type, bool>)
    {
        ImGui::Checkbox(label, &component);
    } else if constexpr (std::is_same_v<type, int>)
    {
        ImGui::InputInt(label, &component);
    } else if constexpr (std::is_same_v<type, std::string>)
    {
        ImGui::InputText(label, &component);
    } else if constexpr (std::is_same_v<type, Range<float>>)
    {
        float x = component.Get();
        if (ImGui::SliderFloat(label, &x, component.Min, component.Max, "%.2f"))
        {
            component.Set(x);
        }
    } else if constexpr (std::is_same_v<type, Range<int>>)
    {
        int x = component.Get();
        if (ImGui::SliderInt(label, &x, component.Min, component.Max, "%d"))
        {
            component.Set(x);
        }
    } else if constexpr (std::is_same_v<type, size_t> || std::is_same_v<type, uint32_t>)
    {
        ImGui::InputScalar(label, ImGuiDataType_U32, &component);
    } else if constexpr (std::is_same_v<type, Vector2>)
    {
        ImGui::DragFloat2(label, &component.x, 0.01f);
    } else if constexpr (std::is_same_v<type, WorldAnchor>)
    {
        constexpr const char* anchorNames[] = {
            "TOP_LEFT", "TOP_CENTER", "TOP_RIGHT", "MIDDLE_LEFT", "MIDDLE_CENTER", "MIDDLE_RIGHT", "BOTTOM_LEFT",
            "BOTTOM_CENTER", "BOTTOM_RIGHT"
        };
        int anchorInt = static_cast<int>(component);
        if (ImGui::Combo(TextFormat("Anchor##%s", label), &anchorInt, anchorNames, 9))
        {
            component = static_cast<WorldAnchor>(anchorInt);
        }
    } else if constexpr (std::is_same_v<type, SpriteSelector>)
    {
        constexpr float size = 32.0f;
        const SpriteManager& sprites = assetManager.Sprites;
        if (component.Id == 0)
        {
            if (ImGui::Button("##xx", {size, size}))
            {
                ImGui::OpenPopup("sprite_popup");
            }
        } else if (const SpriteData sprite = sprites.FromId(component.Id); ImGui::ImageButton(
            "##xx", sprite.Tex.id, {size, size}))
        {
            ImGui::OpenPopup("sprite_popup");
        }
        if (ImGui::BeginPopup("sprite_popup"))
        {
            int i = 0;
            for (const auto& [id, index] : sprites.Ids)
            {
                ImGui::PushID(i);
                if (ImGui::ImageButton("##image", sprites.Data[index].Tex.id, {size, size}))
                {
                    component.Id = id;
                    ImGui::CloseCurrentPopup();
                }
                if (constexpr int ImagesPerRow = 4; i % ImagesPerRow != ImagesPerRow - 1)
                {
                    ImGui::SameLine();
                }
                ImGui::PopID();
                i++;
            }
            ImGui::EndPopup();
        }
    } else if constexpr (visit_struct::traits::is_visitable<type>())
    {
        visit_struct::for_each(component, [&](const char* fName, auto& fValue)
        {
            ResolveComponent((std::string(fName) + "##" + s + std::to_string(i)).c_str(), fValue, assetManager, i);
        });
    } else
    {
        ImGui::Text("%s field type has unsupported type %s", label, typeid(type).name());
    }

    return false;
}

#endif //SHEEP_GOES_DEVILE_RESOLVE_COMPONENT_HPP
