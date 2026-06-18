#include "AssetManager.h"

void AssetManager::LoadAll(EditorSceneOld& editor)
{
    Sprites.LoadAll();
    Icons.LoadAll();
    Levels.LoadAll(editor);
}

void AssetManager::Reload()
{
    Sprites.Reload();
    Icons.Reload();
//    Levels.Reload();
}

void AssetManager::SaveAll() const
{
    Sprites.SaveAll();
}
