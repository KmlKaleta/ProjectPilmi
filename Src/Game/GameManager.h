#pragma once
#include <raylib.h>
#include "GameMap.h"
#include "AnimationData.h"

struct AssetManager;

struct GameManager
{
    Camera2D Camera;
    GameMap World;

    int Characters[3] = {0,1,2};
    AnimationData Anim[3] = {};
    float Positions[3] = {-200, 3, 100};
    int Velocities[3] = {1, 1, 0};
    bool flip[3] = {};

    void Init();

    void Update(AssetManager& assetManager);
};
