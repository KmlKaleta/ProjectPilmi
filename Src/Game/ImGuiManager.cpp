#include "ImGuiManager.h"
#include "GameManager.h"
#include <imgui.h>
#include "AssetManager.h"
#include "SpriteGeneric.h"
#include <assert.h>

SpriteGeneric GetSprite(int index, AssetManager &AssetManager)
{
    if (index < AssetManager::SPRITE_COUNT)
    {
        SpriteData &sprite = AssetManager.Sprites[index];
        SpriteGeneric gen{sprite};
        gen.Raw(sprite);
        return gen;
    }

    index -= AssetManager::SPRITE_COUNT;
    if (index < AssetManager::ATLAS_COUNT)
    {
        SpriteAtlas &atlas = AssetManager.Atlases[index];
        SpriteGeneric gen{atlas.Sprite};
        gen.Atlas(atlas);
        return gen;
    }

    assert(index - AssetManager::ATLAS_COUNT < AssetManager::ANIMATION_COUNT);
    AnimationTexture &anim = AssetManager.Animations[index - AssetManager::ATLAS_COUNT];
    SpriteGeneric gen{anim.Sprite};
    gen.Animation(anim);
    return gen;
}

void ImGuiManager::SpriteEditorWindow(GameManager &gameManager, AssetManager &assetManager)
{
    int index = std::abs(SpriteIndex) % (AssetManager::SPRITE_COUNT + AssetManager::ATLAS_COUNT + AssetManager::ANIMATION_COUNT);
    SpriteGeneric& generic = GetSprite(index, assetManager);

    ImGui::Begin("Sprite Editor");

    ImGui::Checkbox("Show sprite", &ShowSprite);
    ImGui::InputInt("Sprite Index:", &SpriteIndex, 1, 10);

    ImGui::InputFloat("Scale", &generic.Sprite.Scale);
    ImGui::Text("Size: (%.3f, %.3f)", generic.Sprite.Tex.width * generic.Sprite.Scale, generic.Sprite.Tex.height * generic.Sprite.Scale);

    ImGui::InputFloat2("Pivot:", &generic.Sprite.Pivot.x);
    ImGui::InputFloat2("Position:", &SpritePosition.x);

    ImGui::InputInt("Row:", &Row, 1, 10);
    ImGui::InputInt("Column:", &Column, 1, 10);

    ImGui::End();

    if (!ShowSprite)
    {
        return;
    }

    SpriteEditorCamera.offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    BeginMode2D(SpriteEditorCamera);

    int row = Row % generic.RowCounts.size();
    generic.Render(SpritePosition, Column % generic.RowCounts[row], row, false);

    DrawLine(-500, 0, 500, 0, RED);
    DrawLine(0, -500, 0, 500, GREEN);

    EndMode2D();
}

void ImGuiManager::Update(GameManager &gameManager, AssetManager &assetManager)
{
    if (IsKeyPressed(KEY_F10))
    {
        Enable = !Enable;
    }

    if (!Enable)
    {
        return;
    }

    ImGui::Begin("Game Control");

    ImGui::InputFloat("Zoom:", &Zoom, 0.1, 1, "%.2f");
    if (Zoom <= 0)
    {
        Zoom = 0.01f;
    }

    gameManager.Camera.zoom = Zoom;
    SpriteEditorCamera.zoom = Zoom;

    ImGui::End();

    SpriteEditorWindow(gameManager, assetManager);
}