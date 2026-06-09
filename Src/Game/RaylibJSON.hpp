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
    vec.x = j.value("x", 0.f);
    vec.y = j.value("y", 0.f);
}

#endif //SHEEP_GOES_DEVILE_RAYLIB_JSON_HPP
