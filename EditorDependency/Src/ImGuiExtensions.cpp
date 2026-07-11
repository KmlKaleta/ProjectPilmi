//
// Created by Kamil on 24.06.2026.
//
#include "ImGuiExtensions.h"
#include "imgui.h"
#include "Renderer.h"
#include "SpriteData.h"
#include "SpriteManager.h"

void ImGui::DockingSetup()
{
    const ImGuiViewport* viewport = GetMainViewport();

    SetNextWindowPos(viewport->Pos);
    SetNextWindowSize(viewport->Size);
    SetNextWindowViewport(viewport->ID);

    // Remove host padding
    PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

    constexpr ImGuiWindowFlags flags =
            ImGuiWindowFlags_NoDocking |
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoBringToFrontOnFocus |
            ImGuiWindowFlags_NoNavFocus |
            ImGuiWindowFlags_NoBackground;

    Begin("DockSpaceHost", nullptr, flags);

    DockSpace(
        GetID("MainDockSpace"),
        ImVec2(0, 0),
        ImGuiDockNodeFlags_PassthruCentralNode
    );

    End();

    PopStyleVar(3);
}

// void ImGui::WorldPositionEdit(const char* label, WorldPosition* position)
// {
//     DragFloat2(TextFormat("Position##%s", label), &position->Value.x);
//
//     constexpr const char* anchorNames[] = { "TOP_LEFT", "TOP_CENTER", "TOP_RIGHT", "MIDDLE_LEFT", "MIDDLE_CENTER", "MIDDLE_RIGHT", "BOTTOM_LEFT", "BOTTOM_CENTER", "BOTTOM_RIGHT" };
//     int anchorInt = static_cast<int>(position->Anchor);
//     Combo(TextFormat("Anchor##%s", label), &anchorInt, anchorNames, 9);
//     position->Anchor = static_cast<WorldAnchor>(anchorInt);
// }
//
// void ImGui::RendererEdit(const char* label, Renderer* renderer, const SpriteManager& sprites)
// {
//     Text(label);
//
//     constexpr float size = 32.0f;
//     if (renderer->Sprite == 0)
//     {
//         if (Button("##xx", {size, size}))
//         {
//             OpenPopup("sprite_popup");
//         }
//     } else if (SpriteData s = sprites.FromId(renderer->Sprite); ImageButton("##xx", s.Tex.id, {size, size}))
//     {
//         OpenPopup("sprite_popup");
//     }
//
//     if (BeginPopup("sprite_popup"))
//     {
//         int i = 0;
//         for (const auto& [id, index] : sprites.Ids)
//         {
//             PushID(i);
//
//             if (ImageButton("##image", sprites.Data[index].Tex.id, {size, size}))
//             {
//                 renderer->Sprite = id;
//                 CloseCurrentPopup();
//             }
//
//             if (constexpr int ImagesPerRow = 4; i % ImagesPerRow != ImagesPerRow - 1)
//             {
//                 SameLine();
//             }
//             PopID();
//             i++;
//         }
//
//         EndPopup();
//     }
//
//     WorldPositionEdit("Position", &renderer->Position);
//     DragFloat("Scale", &renderer->LocalScale);
//     Checkbox("Flip", &renderer->Flip);
//     InputInt("Texture X", &renderer->TexX);
//     InputInt("Texture Y", &renderer->TexY);
// }
//
// void ImGui::SpriteDataEdit(const char* label, SpriteData* spriteData)
// {
//     Text(label);
//     DragFloat2("Pivot", &spriteData->Pivot.x);
//     DragFloat("Scale", &spriteData->Scale);
//
//     int rowCount = static_cast<int>(spriteData->RowCounts.size());
//     InputInt("Row count", &rowCount);
//     if (rowCount < 1)
//     {
//         rowCount = 1;
//     }
//
//     spriteData->RowCounts.resize(std::abs(rowCount));
//     int max = 1;
//     for (size_t i = 0; i < spriteData->RowCounts.size(); i++)
//     {
//         int& currentRowCount = spriteData->RowCounts[i];
//
//         if (currentRowCount >= max)
//         {
//             max = currentRowCount;
//             spriteData->RowCountMax = currentRowCount;
//         }
//
//         std::string r{"Row "};
//         r += std::to_string(i);
//         r += ':';
//         InputInt(r.c_str(), &currentRowCount);
//         if (currentRowCount < 1)
//         {
//             currentRowCount = 1;
//         }
//     }
// }