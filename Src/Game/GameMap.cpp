#include <raylib.h>
#include "GameMap.h"
#include "AssetManager.h"

void GameMap::Render(AssetManager &assetManager, Rectangle cameraRect)
{
    Indexer2 indexer{(int)cameraRect.width + 4, (int)cameraRect.height + 2};
    size_t count = indexer.Count();
    Coords2 startBlock = Map.Translate({cameraRect.x + 2, cameraRect.y +2 });

    Vector2 firstBlock = Map.UnMap(0);
    Vector2 lastBlock = Map.UnMap(Map.Count() - 1);

    // for (size_t i = 0; i < count; i++)
    // {
    //     Coords2 cell = startBlock + indexer.FromIndex(i);
    //     if (!Map.Indexer.IsValid(cell))
    //     {
    //         continue;
    //     }

    //     Vector2 pos = Map.UnMap(cell);
    //     DrawTexturePro(assetManager.Atlas, {32,0,32,32}, {0,0,1,1}, pos, 0, WHITE);
    // }

    DrawTexturePro(assetManager.Atlas, {32,0,32,32}, {0,0,1,1}, Map.UnMap(0), 0, WHITE);
    DrawRectangleLinesEx({firstBlock.x, firstBlock.y, lastBlock.x - firstBlock.x, lastBlock.y - firstBlock.y}, 0.1f, BLUE);
}