//
// Created by Kamil on 28.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_GAME_SYSTEMS_UPDATE_ARGS_H
#define SHEEP_GOES_DEVILE_GAME_SYSTEMS_UPDATE_ARGS_H
#include "WorldScreenBounds.hpp"
#include "AssetManager.h"

struct GameSystemsUpdateArgs
{
    entt::registry& Registry;
    float DeltaTime;
    const Vector2 MouseWorldPosition;;
    Camera2D& Camera;
    AssetManager& Assets;
    const WorldScreenBounds ScreenBounds;
    bool CanCaptureMouse;
    bool CanCaptureKeyboard;

    GameSystemsUpdateArgs(AssetManager& assets, Camera2D& camera, const bool canCaptureMouse,
                          const bool canCaptureKeyboard) : Registry(assets.Levels.CurrentLevel().Entities.Registry),
                                                           DeltaTime(std::min(GetFrameTime(), 0.25f)),
                                                           MouseWorldPosition(
                                                               GetScreenToWorld2D(GetMousePosition(), camera)),
                                                           Camera(camera),
                                                           Assets(assets),
                                                           ScreenBounds(camera),
                                                           CanCaptureMouse(canCaptureMouse),
                                                           CanCaptureKeyboard(canCaptureKeyboard)
    {
    }
};

#endif //SHEEP_GOES_DEVILE_GAME_SYSTEMS_UPDATE_ARGS_H
