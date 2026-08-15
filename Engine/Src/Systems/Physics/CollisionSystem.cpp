//
// Created by Kamil on 28.06.2026.
//
#include "../GameSystemsUpdateArgs.h"
#include "CollisionSystem.h"

inline Rectangle GetBoxCollider(const Vector2 pos, const float scale, const PhysicsBoxComponent& box)
{
    return box.GetRectangle(pos, scale);
}

inline Rectangle GetBoxCollider(const RendererComponent& renderer, const PhysicsBoxComponent& box,
                                const WorldScreenBounds bounds)
{
    return GetBoxCollider(renderer.Data.Position.GetRelative(bounds), renderer.Data.LocalScale, box);
}

inline void ResolveSeparation(
    PhysicsBodyComponent& body,
    RendererComponent& dynamicRenderer,
    const Vector2& pos,
    const Rectangle& dynamicCollider,
    const Rectangle& staticCollider,
    const Vector2& dynamicMin, const Vector2& dynamicMax,
    const Vector2& staticMin, const Vector2& staticMax,
    const GameSystemsUpdateArgs& args)
{
    if (!CheckCollisionRecs(dynamicCollider, staticCollider))
    {
        return;
    }

    float overlapX = std::min(dynamicMax.x, staticMax.x) - std::max(dynamicMin.x, staticMin.x);
    float overlapY = std::min(dynamicMax.y, staticMax.y) - std::max(dynamicMin.y, staticMin.y);

    Vector2 targetRaylibPos = pos;

    if (overlapX < overlapY)
    {
        const float dynamicCenterX = (dynamicMin.x + dynamicMax.x) / 2.0f;
        const float staticCenterX = (staticMin.x + staticMax.x) / 2.0f;

        if (dynamicCenterX < staticCenterX)
        {
            body.Velocity.x = 0;
            targetRaylibPos.x = pos.x - overlapX;
        } else
        {
            body.Velocity.x = 0;
            targetRaylibPos.x = pos.x + overlapX;
        }
    } else
    {
        float dynamicCenterY = (dynamicMin.y + dynamicMax.y) / 2.0f;
        float staticCenterY = (staticMin.y + staticMax.y) / 2.0f;

        if (dynamicCenterY < staticCenterY)
        {
            body.Velocity.y = 0;
            targetRaylibPos.y = pos.y - overlapY;
        } else
        {
            if (body.Velocity.y >= 0)
            {
                body.Velocity.y = -100;
            }
            targetRaylibPos.y = pos.y + overlapY;
        }
    }

    dynamicRenderer.Data.Position.Value = dynamicRenderer.Data.Position.ToRelative(targetRaylibPos, args.ScreenBounds);
}

inline void ResolveTouch(
    const PhysicsBodyComponent& body,
    const Vector2& dynamicMin, const Vector2& dynamicMax,
    const Vector2& staticMin, const Vector2& staticMax,
    Touch& outTouch)
{
    constexpr float skinWidth = 0.03f;

    const bool overlapX = (dynamicMax.x + skinWidth > staticMin.x) && (dynamicMin.x - skinWidth < staticMax.x);
    const bool overlapY = (dynamicMax.y + skinWidth > staticMin.y) && (dynamicMin.y - skinWidth < staticMax.y);

    // 1. DOWN
    if (overlapX)
    {
        if (dynamicMax.y >= staticMin.y - skinWidth && dynamicMax.y <= staticMin.y + skinWidth)
        {
            outTouch.SetDown(true);
        }
    }

    // 2. UP
    if (overlapX)
    {
        if (dynamicMin.y >= staticMax.y - skinWidth && dynamicMin.y <= staticMax.y + skinWidth)
        {
            outTouch.SetUp(true);
        }
    }

    // 3. LEFT
    if (overlapY)
    {
        if (dynamicMin.x >= staticMax.x - skinWidth && dynamicMin.x <= staticMax.x + skinWidth)
        {
            outTouch.SetLeft(true);
        }
    }

    // 4. RIGHT
    if (overlapY)
    {
        if (dynamicMax.x >= staticMin.x - skinWidth && dynamicMax.x <= staticMin.x + skinWidth)
        {
            outTouch.SetRight(true);
        }
    }
}

void CollisionSystem::Update(GameSystemsUpdateArgs& args) const
{
    const auto& dynamicObjects = args.Registry.view<RendererComponent, PhysicsBodyComponent, const
        PhysicsBoxComponent>();
    const auto& staticObjects = args.Registry.view<const RendererComponent, const PhysicsBoxComponent>(
        entt::exclude<PhysicsBodyComponent>);

    for (const auto& dynamicObject : dynamicObjects)
    {
        PhysicsBodyComponent& body = dynamicObjects.get<PhysicsBodyComponent>(dynamicObject);
        body.Touch.Value = {};

        auto& dynamicRenderer = dynamicObjects.get<RendererComponent>(dynamicObject);
        const auto& dynamicBox = dynamicObjects.get<PhysicsBoxComponent>(dynamicObject);

        for (const auto& staticObject : staticObjects)
        {
            Vector2 pos = dynamicRenderer.Data.Position.GetRelative(args.ScreenBounds);

            Rectangle dynamicCollider = GetBoxCollider(pos, dynamicRenderer.Data.LocalScale, dynamicBox);

            const auto& staticRenderer = staticObjects.get<RendererComponent>(staticObject);
            const auto& staticBox = staticObjects.get<PhysicsBoxComponent>(staticObject);
            const auto& staticCollider = GetBoxCollider(staticRenderer, staticBox, args.ScreenBounds);

            Vector2 dynamicMin = {dynamicCollider.x, dynamicCollider.y};
            Vector2 dynamicMax = {
                dynamicCollider.x + dynamicCollider.width, dynamicCollider.y + dynamicCollider.height
            };

            const Vector2 staticMin = {staticCollider.x, staticCollider.y};
            const Vector2 staticMax = {
                staticCollider.x + staticCollider.width, staticCollider.y + staticCollider.height
            };

            ResolveSeparation(body, dynamicRenderer, pos, dynamicCollider, staticCollider,
                              dynamicMin, dynamicMax, staticMin, staticMax, args);

            pos = dynamicRenderer.Data.Position.GetRelative(args.ScreenBounds);
            dynamicCollider = GetBoxCollider(pos, dynamicRenderer.Data.LocalScale, dynamicBox);
            dynamicMin = {dynamicCollider.x, dynamicCollider.y};
            dynamicMax = {dynamicCollider.x + dynamicCollider.width, dynamicCollider.y + dynamicCollider.height};

            ResolveTouch(body, dynamicMin, dynamicMax, staticMin, staticMax, body.Touch.Value);
        }
    }
}
