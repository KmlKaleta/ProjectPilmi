#pragma once

#include "Indexer2.h"
#include <raymath.h>
#include <cmath>

struct Indexer2Map
{
    Indexer2 Indexer;
    Vector2 Offset = {};
    float CellSize = 1;

    Vector2 Snap(Vector2 position)
    {
        Vector2 relativePosition = position / CellSize - Offset;
        return {std::floor(relativePosition.x), std::floor(relativePosition.y)};
    }

    Coords2 Translate(Vector2 position)
    {
        Vector2 snapped = Snap(position);
        return Coords2{(int)snapped.x, (int)snapped.y};
    }

    Vector2 UnMap(Coords2 coord)
    {
        return Vector2{(float)coord.X * CellSize, (float)coord.Y * CellSize} + Offset;
    }

    Vector2 UnMap(int index)
    {
        return UnMap(Indexer.FromIndex(index));
    }

    void SetCenter(Vector2 newCenter)
    {
        float halfWidth = Indexer.Width * CellSize / 2 + 0.5f;
        float halfHeight = Indexer.Height * CellSize / 2 + 0.5f;

        Offset = newCenter - Vector2{halfWidth, halfHeight};
    }

    size_t Count()
    {
        return Indexer.Count();
    }
};
