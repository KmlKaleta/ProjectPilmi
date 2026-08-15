//
// Created by Kamil on 27.06.2026.
//

#include "SpriteEditorUI.h"
#include "imgui.h"
#include "ImGuiExtensions.h"
#include "ResolveComponent.hpp"
#include "../SpritesExplorer.h"
#include "../SpriteEditor.h"
#include "misc/cpp/imgui_stdlib.h"
#include "StringUtility.hpp"
#include <raymath.h>

void SpriteEditorUI::Draw(SpriteEditor& editor, SpritesExplorer& explorer) const
{
    ImGui::Begin("Sprite Editor");

    if (!explorer.AnySelected)
    {
        ImGui::Text("No Sprite Selected");
        ImGui::End();
        return;
    }

    SpritePath& selected = explorer.Paths[explorer.Ids[explorer.Selected]];
    if (selected.Sprite.Tex.id == 0)
    {
        ImGui::Text("No Texture Loaded");
        ImGui::End();
        return;
    }

    ImGui::Text("Id %llu", selected.Id.Value);

    std::string name = selected.Name;
    ImGui::InputText("##", &name);
    if (ImGui::IsItemDeactivatedAfterEdit() && !IsNullOrWhiteSpace(name))
    {
        explorer.Rename(selected.Id, name);
    }

    ImGui::SpriteDataEdit("", &selected.Sprite);

    ImGui::Separator();

    ImGui::DragFloat2("Position", &editor.Position.x);
    ImGui::InputInt("Row:", &editor.Row, 1, 10);
    ImGui::InputInt("Column:", &editor.Column, 1, 10);
    ImGui::DragFloat("Scale Factor:", &editor.ScaleFactor, 0.01f);
    editor.ScaleFactor = std::max(0.01f, editor.ScaleFactor);
    if ((editor.ShowCollider = ImGui::CollapsingHeader("Default Collider")))
    {
        ImGui::DragFloat2("Offset", &selected.Sprite.DefaultCollider.Position.x);
        ImGui::DragFloat2("Size", &selected.Sprite.DefaultCollider.Size.x);
    }

    if (ImGui::Button("Apply scale"))
    {
        selected.Sprite.Pivot *= editor.ScaleFactor;
        selected.Sprite.Scale *= editor.ScaleFactor;
        selected.Sprite.DefaultCollider.Position *= editor.ScaleFactor;
        selected.Sprite.DefaultCollider.Size *= editor.ScaleFactor;
        editor.ScaleFactor = 1;
    }

    ImGui::SameLine();
    if (ImGui::Button("Default Offsets"))
    {
        editor.Position = {0, 0};
        editor.ScaleFactor = 1;
        editor.Row = 0;
        editor.Column = 0;
    }

    ImGui::Separator();
    for (int i = 0; i < 3; i++)
    {
        ImGui::PushID(i);

        if (editor.Ghosts[i] != 0)
        {
            const SpriteData& spriteData = explorer.Paths[explorer.Ids[editor.Ghosts[i]]].Sprite;
            const float widthRatio = static_cast<float>(spriteData.Tex.width) / static_cast<float>(spriteData.Tex.
                                         height);
            const float x = 1 / static_cast<float>(spriteData.RowCountMax);
            const float y = 1 / static_cast<float>(spriteData.RowCounts.size());
            ImGui::Image(spriteData.Tex.id,
                         ImVec2(64 * widthRatio / static_cast<float>(spriteData.RowCountMax),
                                64 / static_cast<float>(spriteData.RowCounts.size())), {}, ImVec2(x, y));
        } else
        {
            ImGui::InvisibleButton("##", ImVec2(64, 64));
        }

        if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("sprite_drag"))
            {
                assert(payload->DataSize == sizeof(UUID));
                const UUID& id = *static_cast<const UUID *>(payload->Data);
                editor.Ghosts[i] = id;
            }
            ImGui::EndDragDropTarget();
        }

        ImGui::SameLine();
        if (ImGui::Button("Clear"))
        {
            editor.Ghosts[i] = {};
        }
        ImGui::PopID();
    }
    ImGui::End();
}
