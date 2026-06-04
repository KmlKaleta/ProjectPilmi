// #include <raylib.h>
// #include "GameManager.h"
// #include <random>
// #include "AssetManager.h"
//
// void GameManager::Init()
// {
//     Camera.target = {0, 0};
//     Camera.rotation = 0;
//     Camera.zoom = 1;
//
//     for (size_t i = 0; i < 3; i++)
//     {
//         flip[i] = Velocities[i] < 0;
//     }
//
//     Anim[2].TMax = 0.4;
// }
//
// void GameManager::Update(AssetManager& assetManager)
// {
//     const float deltaTime = GetFrameTime();
//     Vector2 camDir = {};
//
//     if (IsKeyDown(KEY_A))
//         camDir.x -= 1;
//     if (IsKeyDown(KEY_D))
//         camDir.x += 1;
//     if (IsKeyDown(KEY_S))
//         camDir.y += 1;
//     if (IsKeyDown(KEY_W))
//         camDir.y -= 1;
//
//     camDir = Vector2Normalize(camDir);
//     Camera.target += camDir * (300 * deltaTime);
//
//     const auto screenWidth = static_cast<float>(GetScreenWidth());
//     const auto screenHeight = static_cast<float>(GetScreenHeight());
//
//     Camera.offset = {screenWidth / 2.0f, screenHeight / 2.0f};
//     ClearBackground({55, 55, 120, 255});
//     std::ranlux24_base rng(std::random_device{}());
//     Vector2 worldPos = GetScreenToWorld2D(GetMousePosition(), Camera);
//     worldPos.x = -worldPos.x;
//     worldPos.y = -worldPos.y;
//
//     Vector2 min = GetScreenToWorld2D({}, Camera);
//     Vector2 max = GetScreenToWorld2D({screenWidth, screenHeight}, Camera);
//
//     Rectangle cameraRect;
//     cameraRect.x = min.x;
//     cameraRect.y = min.y;
//     cameraRect.width = max.x - min.x;
//     cameraRect.height = max.y - min.y;
//
//     float y = -min.y - 110;
//
//     BeginMode2D(Camera);
//
//     // assetManager.Sprites[AssetManager::SPRITE_CLOUD_BACKGROUND].Render({});
//
//     // assetManager.Sprites[AssetManager::SPRITE_TREE1].Render({100, y});
//     // assetManager.Sprites[AssetManager::SPRITE_TREE2].Render({-100, y}, {0, 0, (float)assetManager.Sprites[AssetManager::SPRITE_TREE2].Tex.width, (float)assetManager.Sprites[AssetManager::SPRITE_TREE2].Tex.height}, 1.3);
//     // assetManager.Sprites[AssetManager::SPRITE_TREE1].Render({400, y}, {0, 0, (float)assetManager.Sprites[AssetManager::SPRITE_TREE1].Tex.width, (float)assetManager.Sprites[AssetManager::SPRITE_TREE1].Tex.height}, 0.5);
//     // assetManager.Sprites[AssetManager::SPRITE_TREE2].Render({-400, y});
//
//     // for (int x = -450, i = 0; x < 450; x += 80, i++)
//     // {
//     //     assetManager.Atlases[AssetManager::ATLAS_FLOWER].Render({(float)x, y}, i, 0);
//     // }
//
//     // for (size_t i = 0; i < 3; i++)
//     // {
//     //     const float speed = 100;
//     //     Positions[i] += Velocities[i] * deltaTime * speed;
//     //     if (std::abs(Positions[i]) >= 500)
//     //     {
//     //         Velocities[i] = -Velocities[i];
//     //         Positions[i] += Velocities[i] * deltaTime * speed;
//     //         flip[i] = Velocities[i] < 0;
//     //     }
//
//     //     AnimationTexture animation = assetManager.Animations[Characters[i]];
//     //     AnimationData &animationData = Anim[i];
//
//     //     animationData.Update(deltaTime, animation.FramesPerAnimation[animationData.Animation]);
//     //     animation.Render({Positions[i], y}, animationData, flip[i]);
//     // }
//
//     // assetManager.Sprites[AssetManager::SPRITE_GRASS].Render({0, y});
//     EndMode2D();
// }
