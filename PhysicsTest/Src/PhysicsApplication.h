//
// Created by Kamil on 14.08.2026.
//

#ifndef SHEEP_GOES_DEVILE_PHYSICS_APPLICATION_H
#define SHEEP_GOES_DEVILE_PHYSICS_APPLICATION_H
#include "AssetManager.h"
#include "PhysicsSimulation.h"
#include "PhysicsSimulationUI.h"

struct PhysicsApplication
{
    AssetManager Assets;
    PhysicsSimulation Simulation;
    PhysicsSimulationUI UI;

    bool Init();
    bool Update();
    void Close();
};
#endif //SHEEP_GOES_DEVILE_PHYSICS_APPLICATION_H
