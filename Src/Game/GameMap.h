#pragma once
#include <vector>
#include "Indexer2Map.h"

struct AssetManager;

struct GameMap
{
    Indexer2Map Map;

    void Create(int width, int height){
        Map = Indexer2Map{{width, height}, {}, 1};
        Map.SetCenter({});
    }

    void Render(AssetManager& assetManager, Rectangle cameraRect);
};
