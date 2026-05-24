#include "Gameplay.h"
#include <raylib.h>
#include <imgui.h>

bool Gameplay::Init(GameplayUpdateArgs &args)
{
    args.Init();

    return true;
}

bool Gameplay::Update(GameplayUpdateArgs &args)
{
    args.ImGuiManager.Update(args.GameManager, args.AssetManager);
    
    if (!args.ImGuiManager.ShowSprite)
    {
        args.GameManager.Update(args.AssetManager);
    }

    DrawFPS(10, 10);
    return true;
}

bool Gameplay::Close(GameplayUpdateArgs &args)
{
    return true;
}
