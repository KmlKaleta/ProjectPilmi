//
// Created by Kamil on 18.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_COMPONENTS_H
#define SHEEP_GOES_DEVILE_COMPONENTS_H
#include "JSON.h"
#include "AnimationData.hpp"
#include "UUID.hpp"
#include "Renderer.h"
#include "Fields/EntityRef.hpp"
#include "Fields/Hide.hpp"
#include "Fields/Range.hpp"
#include "Fields/WorldPosition.hpp"
#include "include/visit_struct/visit_struct.hpp"

// @Component(REQUIRED)
struct TagComponent
{
    std::string Value;
};

bool operator==(const TagComponent& lhs, const TagComponent& rhs);

bool operator!=(const TagComponent& lhs, const TagComponent& rhs);

// @Component(UTILITY)
struct OrderComponent
{
    uint32_t Value = std::numeric_limits<uint32_t>::max();

    operator size_t() const
    {
        return Value;
    }
};

// @Component(ADDITIONAL)
struct ParallaxComponent
{
    Range<float> Strength = Range<float>(0.1f, 2.0f, 1);
};

bool operator==(const ParallaxComponent& lhs, const ParallaxComponent& rhs);

bool operator!=(const ParallaxComponent& lhs, const ParallaxComponent& rhs);

// @Component(ADDITIONAL)
struct RendererComponent
{
    uint32_t LayerOrder = 0;
    Renderer Data;
};

// @Component(UTILITY)
struct EntityGroupComponent
{
    std::vector<EntityRef> Entities;
};

// @Component(UTILITY)
struct EntityGroupChildComponent
{
    EntityRef Value;
};

// @Component(ADDITIONAL)
struct MoveSpeedComponent
{
    Range<float> Value = Range<float>(10.f, 2000.0f, 200);
};

// @Component(ADDITIONAL)
struct PatrolComponent
{
    WorldPosition From = {0, 0};
    WorldPosition To = {500, 0};
    bool Reversed = false;
};

// @Component(ADDITIONAL)
struct RoundComponent
{
    WorldPosition Center;
    Range<float> Radius = Range<float>(10.f, 5000.0f, 400);
    Hide<float> T = 0;
};

// @Component(ADDITIONAL)
struct AnimatorComponent
{
    Hide<AnimationData> Data;
    int Animation{};
    Range<float> FrameTime = Range(0.01f, 1.f, 0.1f);
};

// @Component(TAG)
struct ScaleToScreenTag
{
};

struct MainMenuText
{
    Vector2 Position = {0, 0};
    Range<float> Scale = Range(6.f, 96.f, 64.f);
    Color Color = {0, 0, 0, 255};
};

void to_json(JSON& j, const MainMenuText& text);

void from_json(const JSON& j, MainMenuText& text);

VISITABLE_STRUCT(MainMenuText, Position, Scale, Color);

// @Component(ADDITIONAL)
struct MainMenuComponent
{
    enum class Panel
    {
        MainMenu,
        Settings,
        Credits
    };

    Range<float> TitleScale = Range(0.1f, 5.f, 1.f);
    // @Ignore
    Panel CurrentPanel = Panel::MainMenu;
    MainMenuText SheepText = {{0, 0}};
    MainMenuText GoesText = {{-20, 30}};
    MainMenuText DevileText = {{0, 60}};
};

// @Component(ADDITIONAL)
struct TextComponent
{
    enum class Alignment
    {
        Left,
        Center,
        Right
    };

    WorldPosition Position;
    int FontSize = 16;
    std::string Value;
};

// @Component(ADDITIONAL)
struct PhysicsBoxComponent
{
    Vector2 Position = {0, 0};
    Vector2 Size = {100, 100};

    Rectangle GetRectangle( Vector2 position, float scale) const;
};

struct Touch
{
    bool GetDown() const
    {
        return _value[0];
    }

    void SetDown(const bool value)
    {
        _value[0] = value;
    }

    bool GetUp() const
    {
        return _value[1];
    }

    void SetUp(const bool value)
    {
        _value[1] = value;
    }

    bool GetLeft() const
    {
        return _value[2];
    }

    void SetLeft(const bool value)
    {
        _value[2] = value;
    }

    bool GetRight() const
    {
        return _value[3];
    }

    void SetRight(const bool value)
    {
        _value[3] = value;
    }
private:
    bool _value[4] = {false, false, false, false};
};

void to_json(JSON& j, const Touch& touch);
void from_json(const JSON& j, Touch& touch);

// @Component(ADDITIONAL)
struct PhysicsBodyComponent
{
    Hide<Touch> Touch;
    Vector2 Velocity = {0, 0};
    Range<float> Mass = Range(1.0f, 1000.0f, 1.0f);
};

// @Component(TAG)
struct PlayerControllableTag
{
};

#endif //SHEEP_GOES_DEVILE_COMPONENTS_H
