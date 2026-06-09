#include <raylib.h>
#include "Gameplay.h"

bool Gameplay::Init(GameplayUpdateArgs& args)
{
    args.Init();

    return true;
}

bool Gameplay::Update(GameplayUpdateArgs& args)
{
    if (!args.ImGuiManager.Enable)
    {
        args.EditorScene.Update(args.AssetManager);
        args.EditorUi.AfterEditor(args.EditorScene, args.AssetManager);
    }

    args.ImGuiManager.AfterGame(args.EditorScene, args.AssetManager);

    DrawFPS(10, 10);
    return true;
}

bool Gameplay::Close(GameplayUpdateArgs& args)
{
    return true;
}
