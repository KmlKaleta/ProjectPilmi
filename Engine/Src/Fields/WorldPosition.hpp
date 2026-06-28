//
// Created by Kamil on 28.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_WORLD_POSITION_HPP
#define SHEEP_GOES_DEVILE_WORLD_POSITION_HPP
#include "raylib.h"
#include "RaylibJSON.hpp"
#include "WorldScreenBounds.hpp"

enum class WorldAnchor
{
    TOP_LEFT,
    TOP_CENTER,
    TOP_RIGHT,
    MIDDLE_LEFT,
    MIDDLE_CENTER,
    MIDDLE_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_CENTER,
    BOTTOM_RIGHT
};

struct WorldPosition
{
    Vector2 Value = {};
    WorldAnchor Anchor = WorldAnchor::BOTTOM_CENTER;

    Vector2 ToRelative(Vector2 pos, const WorldScreenBounds& screenBounds) const
    {
        switch (Anchor)
        {
            case WorldAnchor::BOTTOM_CENTER:
                pos.y = screenBounds.Max.y - pos.y;
                break;
            case WorldAnchor::TOP_LEFT:
                pos.x = screenBounds.Min.x + pos.x;
                pos.y = screenBounds.Min.y - pos.y;
                break;
            case WorldAnchor::TOP_CENTER:
                pos.y = screenBounds.Min.y - pos.y;
                break;
            case WorldAnchor::TOP_RIGHT:
                pos.x = screenBounds.Max.x + pos.x;
                pos.y = screenBounds.Min.y - pos.y;
                break;
            case WorldAnchor::MIDDLE_LEFT:
                pos.x = screenBounds.Min.x + pos.x;
                pos.y = -pos.y;
                break;
            case WorldAnchor::MIDDLE_CENTER:
                pos.y = -pos.y;
                break;
            case WorldAnchor::MIDDLE_RIGHT:
                pos.x = screenBounds.Max.x + pos.x;
                pos.y = -pos.y;
                break;
            case WorldAnchor::BOTTOM_LEFT:
                pos.x = screenBounds.Min.x + pos.x;
                pos.y = screenBounds.Max.y - pos.y;
                break;
            case WorldAnchor::BOTTOM_RIGHT:
                pos.x = screenBounds.Max.x + pos.x;
                pos.y = screenBounds.Max.y - pos.y;
                break;
        }

        return pos;
    }

    Vector2 GetRelative(const WorldScreenBounds& screenBounds) const
    {
        return ToRelative(Value, screenBounds);
    }

    void SetRelative(const Vector2 value, const WorldScreenBounds& screenBounds)
    {
        Value = ToRelative(value, screenBounds);
    }
};

inline void to_json(JSON& j, const WorldPosition& component)
{
    j["value"] = component.Value;
    j["anchor"] = component.Anchor;
}

inline void from_json(const JSON& j, WorldPosition& component)
{
    ReadJsonValue(component.Value, j, "value", Vector2());
    ReadJsonValue(component.Anchor, j, "anchor", WorldAnchor::BOTTOM_CENTER);
}

#endif //SHEEP_GOES_DEVILE_WORLD_POSITION_HPP
