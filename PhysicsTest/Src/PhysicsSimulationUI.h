//
// Created by Kamil on 14.08.2026.
//

#ifndef SHEEP_GOES_DEVILE_PHYSICS_SIMULATION_UI_H
#define SHEEP_GOES_DEVILE_PHYSICS_SIMULATION_UI_H
struct PhysicsSimulation;
struct AssetManager;

struct PhysicsSimulationUI
{
    void Update(PhysicsSimulation& simulation, AssetManager& assets) const;
};
#endif //SHEEP_GOES_DEVILE_PHYSICS_SIMULATION_UI_H
