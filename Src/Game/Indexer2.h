#pragma once

struct Coords2
{
    int X, Y;

    Coords2 operator+(Coords2 other)
    {
        return Coords2{X + other.X, Y + other.Y};
    }
};

struct Indexer2
{
    int Width = 1, Height = 1;

    size_t Count()
    {
        return Width * Height;
    }

    Coords2 FromIndex(int index)
    {
        return {index % Width, index / Width};
    }

    int ToIndex(Coords2 coord)
    {
        return coord.X + coord.Y * Width;
    }

    bool IsValid(Coords2 coord)
    {
        return coord.X >= 0 && coord.X < Width &&
               coord.Y >= 0 && coord.Y < Height;
    }
};
