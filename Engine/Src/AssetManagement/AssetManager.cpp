#include "AssetManager.h"

void AssetManager::LoadAll()
{
    Sprites.LoadAll();
    // Icons.LoadAll();
    Levels.LoadAll();
    Text.LoadAll(Language::English);
}
