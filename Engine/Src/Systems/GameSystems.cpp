//
// Created by Kamil on 28.06.2026.
//
#include "GameSystems.h"

void GameSystems::Update(GameSystemsUpdateArgs& args)
{
#define X(t) t##Instance.Update(args);
    GameSystemsMacro(X)
#undef X
}
