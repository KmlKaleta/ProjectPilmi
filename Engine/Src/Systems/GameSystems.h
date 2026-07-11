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

#define GameSystemsMacro(X) \
    X(ParallaxSystem) \
    X(PatrolSystem) \
    X(RenderingSystem) \
    X(RoundSystem) \
    X(AnimationSystem) \
    X(ScaleToScreenSystem) \
    X(MainMenuSystem)

struct GameSystemsUpdateArgs;

struct GameSystems
{
#define X(t) t t##Instance;
    GameSystemsMacro(X)
#undef X
    void Update(GameSystemsUpdateArgs& args);
};


#endif //SHEEP_GOES_DEVILE_GAME_SYSTEMS_H
