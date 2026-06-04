//
// Created by Kamil on 26.05.2026.
//

#include "EditorScene.h"
#include "AssetManager.h"
#include "raygui.h"

void EditorScene::Update(const AssetManager& assetManager)
{
    const Vector2 mouseScreenPos = GetMousePosition();
    const Vector2 mousePos = GetScreenToWorld2D(mouseScreenPos, Camera);
    const float deltaTime = GetFrameTime();

    BeginMode2D(Camera);

    for (const auto& renderer : Renderers)
    {
        renderer.Render(assetManager.Sprites);
    }

    switch (State)
    {
        case EDITOR_PALETTE:
            Palette.Update(mousePos, CanInteract, Renderers, assetManager.Sprites);
            break;
        case EDITOR_RENDERERS:
            RenderersEditor.Update(mousePos, CanInteract, Renderers, assetManager.Sprites);
            break;
        default:
            break;
    }

    // const bool isPressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    // if (!isCursorOnUi && Selector.SelectedIndex >= 0)
    // {
    //     const uint64_t spriteId = Selector.Buttons[Selector.SelectedIndex].Data.SpriteId;
    //     const SpriteData spriteData = assetManager.Sprites.FromId(spriteId);
    //     spriteData.Render(mousePos, 0, 0, false, 1.f, {255, 255, 255, 150});
    //
    //     if (isPressed)
    //     {
    //         Renderers.push_back({spriteId, mousePos, 1.f, false, 0, 0});
    //     }
    // }

    EndMode2D();

    // UIIterator it = Ui.GetIterator();
    // const bool isReleased = IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
    // while (it.MoveNext())
    // {
    //     if (Selector.Process(mouseScreenPos, isPressed, isReleased, deltaTime, it, assetManager))
    //     {
    //         continue;
    //     }
    //
    //     if (TexXSelector.Process(TexX, mouseScreenPos, isPressed, isReleased, deltaTime, it, assetManager))
    //     {
    //         continue;
    //     }
    //
    //     if (TexYSelector.Process(TexY, mouseScreenPos, isPressed, isReleased, deltaTime, it, assetManager))
    //     {
    //         continue;
    //     }
    //
    //     const UIElement* current = it.Current();
    //     current->Render(current->CalculateRect());
    // }
    //
    // Selector.SetTextureX(TexX, assetManager.Sprites);
    // Selector.SetTextureY(TexY, assetManager.Sprites);
}

void EditorScene::Reset(const AssetManager& assetManager)
{
    *this = EditorScene();
    Init(assetManager);
}

void EditorScene::Init(const AssetManager& assetManager)
{
    Camera.target = {0, 0};
    Camera.rotation = 0;
    Camera.zoom = 1;


    const auto screenWidth = static_cast<float>(GetScreenWidth());
    const auto screenHeight = static_cast<float>(GetScreenHeight());
    Camera.offset = {screenWidth / 2, screenHeight / 2};

    constexpr int width = 300;
    constexpr int height = 800;

    // Ui = UIPanel();
    // auto background = UIElement();
    // background.Rect = {0, 0, width, height};
    // background.Color = {200, 200, 200, 255};
    // background.Anchor = UIElement::TOP_RIGHT;
    // background.Parent = nullptr;
    // UIElement* backgroundPtr = Ui.AddElement(background);
    //
    // auto selectorElement = UIElement();
    // selectorElement.Padding = 0;
    // selectorElement.Anchor = UIElement::TOP_LEFT;
    // selectorElement.Parent = backgroundPtr;
    // selectorElement.Rect = {0, 0, 100, 500};
    // selectorElement.WidthUnits = UIElement::PERCENTAGE;
    // Selector = SpriteSelector::AddToPanel(selectorElement, 3, assetManager.Sprites, Ui);
    //
    // auto xSelectorElement = UIElement();
    // xSelectorElement.Padding = 0;
    // xSelectorElement.Anchor = UIElement::TOP_LEFT;
    // xSelectorElement.Parent = backgroundPtr;
    // xSelectorElement.Rect = {0, 500, 100, 20};
    // xSelectorElement.WidthUnits = UIElement::PERCENTAGE;
    // TexXSelector = IntSelector::AddToPanel(xSelectorElement, "Texture X:", Ui);
    //
    // auto ySelectorElement = UIElement();
    // ySelectorElement.Padding = 0;
    // ySelectorElement.Anchor = UIElement::TOP_LEFT;
    // ySelectorElement.Parent = backgroundPtr;
    // ySelectorElement.Rect = {0, 520, 100, 20};
    // ySelectorElement.WidthUnits = UIElement::PERCENTAGE;
    // TexYSelector = IntSelector::AddToPanel(ySelectorElement, "Texture Y:", Ui);

    // ui.Rect = {-halfPadding, halfPadding, width, height};
    // ui.Color = ;
    //
    // constexpr int squaresInRow = 3;
    // constexpr float cellSpace = static_cast<float>(width) / squaresInRow;
    // constexpr float rectSpace = cellSpace - padding;
    //
    // int x = 0;
    // int y = 0;
    // for (auto& [id, index] : assetManager.Sprites.Ids)
    // {
    //     if (x >= squaresInRow)
    //     {
    //         x = 0;
    //         y++;
    //     }
    //     const float cellX = cellSpace * static_cast<float>(x);
    //     const float cellY = cellSpace * static_cast<float>(y);
    //     const Rectangle rect = {
    //         cellX + static_cast<float>(halfPadding), cellY + static_cast<float>(halfPadding),
    //         rectSpace, rectSpace
    //     };
    //
    //     ui.AddInteractable(rect, {id, 1, 0, 0}, false, INTERACTION_SELECT_SPRITE);
    //     x++;
    // }
    //
    // const uint64_t arrowsId = StringToHash("Arrows");
    // ui.Labels.push_back({"Texture X:", GetFontDefault(), {halfPadding, 500 + halfPadding}, 20});
    // ui.AddInteractable({-halfPadding, 500 + halfPadding, 20, 20}, {arrowsId, 1, 2, 0, {150,150,150,255}}, true,
    //                    INTERACTION_INCREMENT_TEX_X);
    //
    // //ui.AddLabel(std::to_string());
    //
    // ui.AddInteractable({-halfPadding - 50 - halfPadding - halfPadding - halfPadding, 500 + halfPadding, 20, 20},
    //                    {arrowsId, 1, 1, 0, {150,150,150,255}}, true, INTERACTION_DECREMENT_TEX_X);
    //
    // ui.Labels.push_back({"Texture Y:", GetFontDefault(), {halfPadding, 530 + halfPadding}, 20});
    //ui.AddInteractable({-halfPadding, 530 + halfPadding, 20, 20}, {checkMarkId, 1, 0, 0, GREEN}, true,
    //                   INTERACTION_TEX_Y);
}
