//
// Created by Kamil on 14.08.2026.
//
#include "Systems/GameSystemsUpdateArgs.h"
#include "PhysicsSystem.h"

void PhysicsSystem::Update(GameSystemsUpdateArgs& args)
{
    _fixedFrameRate.Update(args.DeltaTime);

    const float deltaTime = args.DeltaTime;
    args.DeltaTime = FixedFrameRate60FPS::fixedDeltaTime;
    while (_fixedFrameRate.Step())
    {
        _velocity.Update(args);
        _collision.Update(args);
    }
    args.DeltaTime = deltaTime;
    _debug.Update(args);
}
