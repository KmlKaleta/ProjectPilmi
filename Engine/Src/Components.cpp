//
// Created by Kamil on 18.06.2026.
//
#include "Components.h"
#include "RaylibJSON.hpp"

bool operator==(const TagComponent& lhs, const TagComponent& rhs)
{
    return lhs.Value == rhs.Value;
}

bool operator!=(const TagComponent& lhs, const TagComponent& rhs)
{
    return !(lhs == rhs);
}

bool operator==(const ParallaxComponent& lhs, const ParallaxComponent& rhs)
{
    return lhs.Strength.Get() == rhs.Strength.Get();
}

bool operator!=(const ParallaxComponent& lhs, const ParallaxComponent& rhs)
{
    return !(lhs == rhs);
}

// void RendererComponent::SetPositionRelative(const Camera2D& camera, const Vector2& position)
// {
//     Vector2 pos = position;
//
//     switch (Anchor)
//     {
//         case RenderAnchor::BOTTOM_CENTER:
//             pos.y = Data.Position.y - pos.y;
//             break;
//     }
//
//     Data.Position = pos;
// }

void to_json(JSON& j, const MainMenuText& text)
{
    j["position"] = text.Position;
    j["scale"] = text.Scale;
    j["color"] = ColorNormalize(text.Color);
}

void from_json(const JSON& j, MainMenuText& text)
{
    ReadJsonValue(text.Position, j, "position", text.Position);
    ReadJsonValue(text.Scale, j, "scale", text.Scale);
    ReadJsonValue(text.Color, j, "color", text.Color);
}

Rectangle PhysicsBoxComponent::GetRectangle(const Vector2 position, const float scale) const
{
        return {
            position.x + (Position.x - Size.x / 2) * scale,
            position.y + (Position.y - Size.y) * scale,
            Size.x * scale,
            Size.y * scale
        };
}

void to_json(JSON& j, const Touch& touch)
{
    j["up"] = touch.GetUp();
    j["left"] = touch.GetLeft();
    j["right"] = touch.GetRight();
    j["down"] = touch.GetDown();
}

void from_json(const JSON& j, Touch& touch)
{
    bool x = false;
    ReadJsonValue(x, j, "up", false);
    touch.SetUp(x);
    ReadJsonValue(x, j, "left", false);
    touch.SetLeft(x);
    ReadJsonValue(x, j, "right", false);
    touch.SetRight(x);
    ReadJsonValue(x, j, "down", false);
    touch.SetDown(x);
}
