//
// Created by Kamil on 26.06.2026.
//
#include "SpritesExplorerUI.h"

#include "imgui.h"
#include "../SpriteEditor.h"
#include "../SpritesExplorer.h"

void DrawRoot(SpritesExplorer& explorer, SpriteEditor& editor, const SpriteDirectory& directory)
{
    ImGui::Indent();
    for (auto& child : directory.Children)
    {
        if (!child.IsDirectory)
        {
            const SpritePath spritePath = explorer.Paths[child.Index];
            if (ImGui::Selectable(("##" + spritePath.Path).c_str(), explorer.Selected == spritePath.Id,
                                  ImGuiSelectableFlags_AllowOverlap))
            {
                if (explorer.AnySelected)
                {
                    explorer.Save(explorer.Ids[explorer.Selected]);
                }

                explorer.Selected = spritePath.Id;
                explorer.AnySelected = true;
                editor.ScaleFactor = 1;
            }

            if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
            {
                // Set payload to carry the index of our item (could be anything)
                ImGui::SetDragDropPayload("sprite_drag", &spritePath.Id, sizeof(UUID));
                // Display preview (could be anything, e.g. when dragging an image we could decide to display
                // the filename and a small preview of the image, etc.)
                ImGui::Text(spritePath.GetFileName().c_str());
                const float widthRatio = static_cast<float>(spritePath.Sprite.Tex.width) / static_cast<float>(spritePath
                                             .Sprite.
                                             Tex.
                                             height);
                ImGui::Image(spritePath.Sprite.Tex.id, ImVec2(64 * widthRatio, 64));
                ImGui::EndDragDropSource();
            } else if (ImGui::IsItemHovered())
            {
                ImGui::BeginTooltip();
                ImGui::Text(spritePath.Path.c_str());

                const float widthRatio = static_cast<float>(spritePath.Sprite.Tex.width) / static_cast<float>(spritePath
                                             .Sprite.
                                             Tex.
                                             height);
                const SpriteData& spriteData = spritePath.Sprite;
                const float x = 1 / static_cast<float>(spriteData.RowCountMax);
                const float y = 1 / static_cast<float>(spriteData.RowCounts.size());
                ImGui::Image(spritePath.Sprite.Tex.id,
                             ImVec2(128 * widthRatio / static_cast<float>(spriteData.RowCountMax),
                                    128.f / static_cast<float>(spriteData.RowCounts.size())), {}, ImVec2(x, y));
                ImGui::Separator();
                ImGui::Image(spritePath.Sprite.Tex.id, ImVec2(128 * widthRatio, 128));
                ImGui::EndTooltip();
            }
            ImGui::SameLine();
            ImGui::Text(spritePath.Name.c_str());
            continue;
        }

        const SpriteDirectory& dir = explorer.Directories[child.Index];
        if (ImGui::CollapsingHeader(dir.Name.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
        {
            if (ImGui::BeginDragDropTarget())
            {
                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("sprite_drag"))
                {
                    assert(payload->DataSize == sizeof(UUID));
                    const UUID& id = *static_cast<const UUID *>(payload->Data);
                    explorer.Move(id, child.Index);
                }
                ImGui::EndDragDropTarget();
            }

            DrawRoot(explorer, editor, dir);
        } else if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("sprite_drag"))
            {
                assert(payload->DataSize == sizeof(UUID));
                const UUID& id = *static_cast<const UUID *>(payload->Data);
                explorer.Move(id, child.Index);
            }
            ImGui::EndDragDropTarget();
        }
    }
    ImGui::Unindent();
}

void SpritesExplorerUI::Draw(SpritesExplorer& explorer, SpriteEditor& editor) const
{
    ImGui::Begin("Explorer");

    const float footerHeight = ImGui::GetFrameHeightWithSpacing() * 2.0f;

    ImGui::BeginChild("ExplorerScroll", ImVec2(0, -footerHeight), true);
    if (ImGui::CollapsingHeader("Sprites", ImGuiTreeNodeFlags_DefaultOpen))
    {
        if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("sprite_drag"))
            {
                assert(payload->DataSize == sizeof(UUID));
                const UUID& id = *static_cast<const UUID *>(payload->Data);
                explorer.Move(id, 0);
            }
            ImGui::EndDragDropTarget();
        }
        DrawRoot(explorer, editor, explorer.GetRoot());
    } else if (ImGui::BeginDragDropTarget())
    {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("sprite_drag"))
        {
            assert(payload->DataSize == sizeof(UUID));
            const UUID& id = *static_cast<const UUID *>(payload->Data);
            explorer.Move(id, 0);
        }
        ImGui::EndDragDropTarget();
    }

    ImGui::EndChild();

    if (ImGui::Button("Refresh"))
    {
        explorer.Refresh();
    }
    ImGui::End();
}
