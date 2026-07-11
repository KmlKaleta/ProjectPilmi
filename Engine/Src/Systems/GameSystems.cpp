//
// Created by Kamil on 28.06.2026.
//
#include "GameSystems.h"
#include "raylib.h"

void GameSystems::Update(GameSystemsUpdateArgs& args)
{
#define X(t) if (WindowShouldClose()) \
    { \
        return; \
    } \
    t##Instance.Update(args);
    GameSystemsMacro(X)
#undef X
}
