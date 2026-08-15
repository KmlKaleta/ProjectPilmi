//
// Created by Kamil on 28.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_GAME_SYSTEMS_H
#define SHEEP_GOES_DEVILE_GAME_SYSTEMS_H

#include "AnimationSystem.h"
#include "ParallaxSystem.h"
#include "PatrolSystem.h"
#include "RenderingSystem.h"
#include "RoundSystem.h"
#include "ScaleToScreenSystem.h"
#include "MainMenuSystem.h"
#include "Physics/PhysicsSystem.h"
#include "Physics/PlayerMovementSystem.h"

#define GameSystemsMacro(X) \
    X(ParallaxSystem) \
    X(PatrolSystem) \
    X(RenderingSystem) \
    X(RoundSystem) \
    X(AnimationSystem) \
    X(ScaleToScreenSystem) \
    X(MainMenuSystem) \
    X(PlayerMovementSystem) \
    X(PhysicsSystem)

struct GameSystemsUpdateArgs;

struct GameSystems
{
#define X(t) t t##Instance{};
    GameSystemsMacro(X)
#undef X
    void Update(GameSystemsUpdateArgs& args);
};


#endif //SHEEP_GOES_DEVILE_GAME_SYSTEMS_H
