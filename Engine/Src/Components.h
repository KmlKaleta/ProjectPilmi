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

#define RequiredComponentNamesMacro(X) \
X(TAG, TagComponent)

#define AdditionalComponentNamesMacro(X) \
X(PARALLAX, ParallaxComponent) \
X(RENDERER, RendererComponent) \
X(MOVE_SPEED, MoveSpeedComponent) \
X(PATROL, PatrolComponent) \
X(ROUND, RoundComponent) \
X(ANIMATOR, AnimatorComponent) \
X(MAIN_MENU, MainMenuComponent) \
X(TEXT, TextComponent)

#define UtilityComponentNamesMacro(X) \
X(ENTITY_GROUP, EntityGroupComponent) \
X(ENTITY_GROUP_CHILD, EntityGroupChildComponent) \
X(ORDER, OrderComponent)

#define TagComponentNamesMacro(X) \
X(SCALE_TO_SCREEN, ScaleToScreenTag)

#define AllComponentNamesMacro(X) \
    RequiredComponentNamesMacro(X) \
    UtilityComponentNamesMacro(X) \
    AdditionalComponentNamesMacro(X)

enum class RequiredComponentType
{
#define X(e, t) e,
    RequiredComponentNamesMacro(X)
#undef X
    COUNT
};

enum class AdditionalComponentType
{
#define X(e, t) e,
    AdditionalComponentNamesMacro(X)
#undef X
    COUNT
};

enum class UtilityComponentType
{
#define X(e, t) e,
    UtilityComponentNamesMacro(X)
#undef X
    COUNT
};

enum class TagComponentType
{
#define X(e, t) e,
    TagComponentNamesMacro(X)
#undef X
    COUNT
};

enum class ComponentType
{
    None = 0,
#define X(e, t) e,
    AllComponentNamesMacro(X)
    TagComponentNamesMacro(X)
#undef X

    COUNT
};

// @Component(REQUIRED)
struct TagComponent
{
    std::string Value;
};

void to_json(JSON& j, const TagComponent& component);

void from_json(const JSON& j, TagComponent& component);

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

void to_json(JSON& j, const OrderComponent& component);

void from_json(const JSON& j, OrderComponent& component);

// @Component(ADDITIONAL)
struct ParallaxComponent
{
    Range<float> Strength = Range<float>(0.1f, 2.0f, 1);
};

void to_json(JSON& j, const ParallaxComponent& component);

void from_json(const JSON& j, ParallaxComponent& component);

bool operator==(const ParallaxComponent& lhs, const ParallaxComponent& rhs);

bool operator!=(const ParallaxComponent& lhs, const ParallaxComponent& rhs);

// @Component(ADDITIONAL)
struct RendererComponent
{
    uint32_t LayerOrder = 0;
    Renderer Data;
};

void to_json(JSON& j, const RendererComponent& component);

void from_json(const JSON& j, RendererComponent& component);

// @Component(UTILITY)
struct EntityGroupComponent
{
    std::vector<EntityRef> Entities;
};

void to_json(JSON&, const EntityGroupComponent&);

void from_json(const JSON&, EntityGroupComponent&);

// @Component(UTILITY)
struct EntityGroupChildComponent
{
    EntityRef Value;
};

void to_json(JSON&, const EntityGroupChildComponent&);

void from_json(const JSON&, EntityGroupChildComponent&);

// @Component(ADDITIONAL)
struct MoveSpeedComponent
{
    Range<float> Value = Range<float>(10.f, 2000.0f, 200);
};

void to_json(JSON& j, const MoveSpeedComponent& component);

void from_json(const JSON& j, MoveSpeedComponent& component);

// @Component(ADDITIONAL)
struct PatrolComponent
{
    WorldPosition From = {0, 0};
    WorldPosition To = {500, 0};
    bool Reversed = false;
};

void to_json(JSON& j, const PatrolComponent& component);

void from_json(const JSON& j, PatrolComponent& component);

// @Component(ADDITIONAL)
struct RoundComponent
{
    WorldPosition Center;
    Range<float> Radius = Range<float>(10.f, 5000.0f, 400);
    float T = 0;
};

void to_json(JSON& j, const RoundComponent& component);

void from_json(const JSON& j, RoundComponent& component);

// @Component(ADDITIONAL)
struct AnimatorComponent
{
    //@Ignored
    AnimationData Data;
    int Animation{};
    Range<float> FrameTime = Range(0.01f, 1.f, 0.1f);
};

void to_json(JSON& j, const AnimatorComponent& component);

void from_json(const JSON& j, AnimatorComponent& component);

// @Component(TAG)
struct ScaleToScreenTag{};

// @Component(ADDITIONAL)
struct MainMenuText
{
    Vector2 Position = {0, 0};
    Range<float> Scale = Range(6.f, 96.f, 64.f);
    Color Color = {0,0,0,255};
};

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
    Hide<Panel> CurrentPanel = Panel::MainMenu;
    MainMenuText SheepText = {{0, 0}};
    MainMenuText GoesText = {{-20, 30}};
    MainMenuText DevileText = {{0, 60}};
};

void to_json(JSON& j, const MainMenuComponent& component);

void from_json(const JSON& j, MainMenuComponent& component);

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

void to_json(JSON& j, const TextComponent& component);

void from_json(const JSON& j, TextComponent& component);

#endif //SHEEP_GOES_DEVILE_COMPONENTS_H
