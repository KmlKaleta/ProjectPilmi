#include "ImGuiSpriteEditor.h"
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

#include "EditorSceneOld.h"
#include "AssetManagement/AssetManager.h"

void ImGuiSpriteEditor::AfterGame(EditorSceneOld& editor, AssetManager& assetManager)
{
    SpriteManager& spritesManager = assetManager.Sprites;
    const auto index = std::abs(Index) % spritesManager.Data.size();
    SpriteData& sprite = spritesManager.Data[index];
    auto& [Name, Path] = spritesManager.Metadata[index];

    const int lastIndex = Index;
    ImGui::InputInt("Sprite Index:", &Index, 1, 10);
    if (lastIndex != Index)
    {
        ScaleFactor = 1;
    }

    ImGui::InputText("Name:", &Name);
    ImGui::InputFloat("Scale", &sprite.Scale);

    int rowCount = static_cast<int>(sprite.RowCounts.size());
    ImGui::InputInt("Row count:", &rowCount);
    if (rowCount < 1)
    {
        rowCount = 1;
    }

    sprite.RowCounts.resize(std::abs(rowCount));
    int max = 1;
    for (size_t i = 0; i < sprite.RowCounts.size(); i++)
    {
        int& currentRowCount = sprite.RowCounts[i];

        if (currentRowCount >= max)
        {
            max = currentRowCount;
            sprite.RowCountMax = currentRowCount;
        }

        std::string r{"Row "};
        r += std::to_string(i);
        r += ':';
        ImGui::InputInt(r.c_str(), &currentRowCount);
        if (currentRowCount < 1)
        {
            currentRowCount = 1;
        }
    }

    ImGui::Text("Full Size: (%.3f, %.3f)", static_cast<float>(sprite.Tex.width) * sprite.Scale,
                static_cast<float>(sprite.Tex.height) * sprite.Scale);
    ImGui::Text("Single Size: (%.3f, %.3f)",
                static_cast<float>(sprite.Tex.width) / static_cast<float>(sprite.RowCountMax) * sprite.Scale,
                static_cast<float>(sprite.Tex.height) / static_cast<float>(sprite.RowCounts.size()) * sprite.Scale);

    ImGui::InputFloat2("Pivot:", &sprite.Pivot.x);
    ImGui::InputFloat2("Position:", &Position.x);

    ImGui::InputInt("Row:", &Row, 1, 10);
    ImGui::InputInt("Column:", &Column, 1, 10);
    ImGui::InputFloat("Scale Factor:", &ScaleFactor);
    ScaleFactor = std::max(0.01f, ScaleFactor);
    if (ImGui::Button("Apply scale"))
    {
        sprite.Pivot *= ScaleFactor;
        sprite.Scale *= ScaleFactor;
        ScaleFactor = 1;
    }


    if (ImGui::Button("Refresh"))
    {
        spritesManager.Reload();
        editor.Reset();
        return;
    }
    ImGui::SameLine();
    if (ImGui::Button("Save"))
    {
        spritesManager.SaveAll();
    }

    ClearBackground(GRAY);

    Camera.offset = {static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) / 2};
    BeginMode2D(Camera);

    const int row = Row % static_cast<int>(sprite.RowCounts.size());
    sprite.Render(Position, Column % sprite.RowCounts[row], row, false, ScaleFactor);

    DrawLine(-500, 0, 500, 0, RED);
    DrawLine(0, -500, 0, 500, GREEN);

    EndMode2D();
}
