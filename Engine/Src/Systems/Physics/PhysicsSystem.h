//
// Created by Kamil on 14.08.2026.
//

#ifndef SHEEP_GOES_DEVILE_PHYSICS_SYSTEM_H
#define SHEEP_GOES_DEVILE_PHYSICS_SYSTEM_H
#include "CollisionSystem.h"
#include "VelocitySystem.h"
#include "PhysicsDebugSystem.h"
#include "FixedFrameRate60FPS.h"

struct GameSystemsUpdateArgs;

struct PhysicsSystem
{
    void Update(GameSystemsUpdateArgs& args);
private:
    VelocitySystem _velocity;
    CollisionSystem _collision;
    PhysicsDebugSystem _debug;
    FixedFrameRate60FPS _fixedFrameRate;
};

#endif //SHEEP_GOES_DEVILE_PHYSICS_SYSTEM_H
