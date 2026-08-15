//
// Created by Kamil on 14.08.2026.
//
#include "PhysicsApplication.h"

bool PhysicsApplication::Init()
{
    Assets.LoadAll();
    Assets.Levels.Load(10861273992076206294u);
    Simulation.Init();
    return true;
}

bool PhysicsApplication::Update()
{
    UI.Update(Simulation, Assets);
    Simulation.Update(Assets);
    if (WindowShouldClose())
    {
        return false;
    }
    DrawFPS(10, 10);
    return true;
}

void PhysicsApplication::Close()
{
}
