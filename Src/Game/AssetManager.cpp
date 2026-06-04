#include "AssetManager.h"

void AssetManager::LoadAll()
{
    Sprites.LoadAll();
    Icons.LoadAll();
}

void AssetManager::Reload()
{
    Sprites.Reload();
    Icons.Reload();
}

void AssetManager::SaveAll() const
{
    Sprites.SaveAll();
}
