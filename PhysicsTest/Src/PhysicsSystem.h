//
// Created by Kamil on 14.08.2026.
//

#ifndef SHEEP_GOES_DEVILE_PHYSICS_SYSTEM_H
#define SHEEP_GOES_DEVILE_PHYSICS_SYSTEM_H
#include "Systems/Physics/CollisionSystem.h"
#include "Systems/Physics/VelocitySystem.h"
#include "FixedFrameRate60FPS.h"
#include "RandomMovementSystem.h"

struct GameSystemsUpdateArgs;

struct PhysicsSystem
{
    void Update(GameSystemsUpdateArgs& args);
private:
    VelocitySystem _velocity;
    CollisionSystem _collision;
    RandomMovementSystem _randomMovement;
    FixedFrameRate60FPS _fixedFrameRate;
};

#endif //SHEEP_GOES_DEVILE_PHYSICS_SYSTEM_H
