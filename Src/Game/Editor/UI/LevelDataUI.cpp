//
// Created by Kamil on 04.06.2026.
//
#include "AssetManagement/LevelManager.h"
#include "Editor/EditorScene.h"
#include "LevelDataUI.h"
#include <raygui.h>


Rectangle LevelDataUI::GetRect() const
{
    return {GetScreenWidth() - Width, 0, Width, GetHeight()};
}

float LevelDataUI::GetHeight() const
{
    return 20 + 5 + 20 + 5 + 20;
}

void LevelDataUI::Draw(EditorScene& editor, LevelManager& levelManager) const
{
    std::string levelCombo;
    for (const auto& [Name] : levelManager.Metadata)
    {
        levelCombo += Name + ";";
    }

    levelCombo.pop_back();

    const float x = GetScreenWidth() - Width;
    int index = static_cast<int>(editor.CurrentLevel);
    GuiComboBox({x, 0, Width, 20}, levelCombo.c_str(), &index);
    if (index != editor.CurrentLevel)
    {
        levelManager.Load(editor, index);
    }

    if (GuiButton({x, 25, Width, 20}, "Save"))
    {
        levelManager.Save(editor);
    }

    if (GuiButton({x, 50, Width, 20}, "New"))
    {
        levelManager.Data.emplace_back();
        levelManager.Metadata.push_back({"New Level"});
        levelManager.Load(editor, static_cast<int>(levelManager.Data.size()) - 1);
    }

}
