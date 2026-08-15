//
// Created by Kamil on 26.06.2026.
//
#include "SpriteEditorScene.h"
#include "SpriteEditor.h"
#include "SpritesExplorer.h"

void SpriteEditorScene::Init()
{
    Camera.target = {0, 0};
    Camera.rotation = 0;
    Camera.zoom = 1;
}


void SpriteEditorScene::Update(SpritesExplorer& explorer, const SpriteEditor& editor)
{
    ClearBackground(GRAY);

    Camera.offset = {static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) / 2};
    BeginMode2D(Camera);

    for (int i = 0; i < 3; i++)
    {
        constexpr Color colors[3] = {{200, 100, 100, 125}, {100, 200, 100, 125}, {100, 100, 200, 125}};
        if (editor.Ghosts[i] == 0)
        {
            continue;
        }

        const SpriteData& sprite = explorer.Paths[explorer.Ids[editor.Ghosts[i]]].Sprite;
        const int row = editor.Row % static_cast<int>(sprite.RowCounts.size());
        sprite.Render({}, editor.Column % sprite.RowCounts[row], row, false, 1, colors[i]);
    }

    if (explorer.AnySelected)
    {
        const SpriteData& sprite = explorer.Paths[explorer.Ids[explorer.Selected]].Sprite;
        const int row = editor.Row % static_cast<int>(sprite.RowCounts.size());
        sprite.Render(editor.Position, editor.Column % sprite.RowCounts[row], row, false, editor.ScaleFactor);
        if (editor.ShowCollider)
        {
            DrawRectangleLinesEx(sprite.GetBounds(editor.Position, editor.ScaleFactor), 1, DARKGREEN);
        }
    }

    DrawLine(-500, 0, 500, 0, RED);
    DrawLine(0, -500, 0, 500, GREEN);

    EndMode2D();
}
