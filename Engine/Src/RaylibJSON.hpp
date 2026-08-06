//
// Created by Kamil on 09.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_RAYLIB_JSON_HPP
#define SHEEP_GOES_DEVILE_RAYLIB_JSON_HPP
#include "JSON.h"
#include "raylib.h"

inline void to_json(JSON& j, const Vector2& vec)
{
    j = {{"x", vec.x}, {"y", vec.y}};
}

inline void from_json(const JSON& j, Vector2& vec)
{
    ReadJsonValue(vec.x, j, "x", 0.f);
    ReadJsonValue(vec.y, j, "y", 0.f);
}

inline void to_json(JSON& j, const Vector4& vec)
{
    j = {{"x", vec.x}, {"y", vec.y}, {"z", vec.z}, {"w", vec.w}};
}

inline void from_json(const JSON& j, Vector4& vec)
{
    ReadJsonValue(vec.x, j, "x", 0.f);
    ReadJsonValue(vec.y, j, "y", 0.f);
    ReadJsonValue(vec.z, j, "z", 0.f);
    ReadJsonValue(vec.w, j, "w", 0.f);
}

#endif //SHEEP_GOES_DEVILE_RAYLIB_JSON_HPP
