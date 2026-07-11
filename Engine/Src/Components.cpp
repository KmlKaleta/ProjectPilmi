//
// Created by Kamil on 18.06.2026.
//
#include "Components.h"
#include "raymath.h"

void to_json(JSON& j, const TagComponent& component)
{
    j["value"] = component.Value;
}

void from_json(const JSON& j, TagComponent& component)
{
    ReadJsonValue(component.Value, j, "value", std::string("No Name"));
}

bool operator==(const TagComponent& lhs, const TagComponent& rhs)
{
    return lhs.Value == rhs.Value;
}

bool operator!=(const TagComponent& lhs, const TagComponent& rhs)
{
    return !(lhs == rhs);
}

void to_json(JSON& j, const OrderComponent& component)
{
    j = component.Value;
}

void from_json(const JSON& j, OrderComponent& component)
{
    ReadJsonValue(component.Value, j, std::numeric_limits<uint32_t>::max());
}

void to_json(JSON& j, const ParallaxComponent& component)
{
    j["strength"] = component.Strength;
}

void from_json(const JSON& j, ParallaxComponent& component)
{
    ReadJsonValue(component.Strength, j, "strength", component.Strength);
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

void to_json(JSON& j, const RendererComponent& component)
{
    j["order"] = component.LayerOrder;
    j["renderer"] = component.Data;
}

void from_json(const JSON& j, RendererComponent& component)
{
    ReadJsonValue(component.LayerOrder, j, "order", component.LayerOrder);
    ReadJsonValue(component.Data, j, "renderer", component.Data);
}

void to_json(JSON& j, const EntityGroupComponent& component)
{
    j = JSON::array();
    for (const auto& [ID] : component.Entities)
    {
        j.emplace_back(ID);
    }
}

void from_json(const JSON& j, EntityGroupComponent& component)
{
    if (!j.is_array())
    {
        return;
    }

    for (const auto& ID : j)
    {
        UUID id{};
        from_json(ID, id);

        if (id != 0){
            component.Entities.emplace_back(id);
        }
    }
}

void to_json(JSON& j, const EntityGroupChildComponent& component)
{
    j = JSON::object();
}

void from_json(const JSON&, EntityGroupChildComponent&)
{
}

void to_json(JSON& j, const MoveSpeedComponent& component)
{
    j = component.Value;
}

void from_json(const JSON& j, MoveSpeedComponent& component)
{
    ReadJsonValue(component.Value, j, component.Value);
}

void to_json(JSON& j, const PatrolComponent& component)
{
    j["from"] = component.From;
    j["to"] = component.To;
    j["reversed"] = component.Reversed;
}

void from_json(const JSON& j, PatrolComponent& component)
{
    ReadJsonValue(component.From, j, "from", component.From);
    ReadJsonValue(component.To, j, "to", component.To);
    ReadJsonValue(component.Reversed, j, "reversed", component.Reversed);
}

void to_json(JSON& j, const RoundComponent& component)
{
    j["position"] = component.Center;
    j["radius"] = component.Radius;
}

void from_json(const JSON& j, RoundComponent& component)
{
    ReadJsonValue(component.Center, j, "position", component.Center);
    ReadJsonValue(component.Radius, j, "radius", component.Radius);
}

void to_json(JSON& j, const AnimatorComponent& component)
{
    j["animation"] = component.Animation;
    j["frame_time"] = component.FrameTime;
}

void from_json(const JSON& j, AnimatorComponent& component)
{
    ReadJsonValue(component.Animation, j, "animation", component.Animation);
    ReadJsonValue(component.FrameTime, j, "frame_time", component.FrameTime);
}

void to_json(JSON& j, const MainMenuComponent& component)
{
    j = JSON::object();
}

void from_json(const JSON& j, MainMenuComponent& component)
{
}

void to_json(JSON& j, const TextComponent& component)
{
    j = component.Value;
}

void from_json(const JSON& j, TextComponent& component)
{
    ReadJsonValue(component.Value, j, std::string("####"));
}
