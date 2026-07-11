//
// Created by Kamil on 09.07.2026.
//
#include "MainMenuSystem.h"

#include "Components.h"
#include "GameSystemsUpdateArgs.h"

void DrawTextCentered(const Rectangle rect, const Font& font, const char* text, const float fontSize, const Color color)
{
    const Vector2 center = {rect.x + rect.width / 2, rect.y + rect.height / 2};
    const Vector2 textSize = MeasureTextEx(font, text, fontSize, 1);
    DrawTextEx(font, text, center - textSize / 2, fontSize, 1, color);
}

bool Button(const Rectangle rect, const char* text, const float fontSize, const Font& font,
            const Vector2 mouseWorldPosition)
{
    if (const bool isMouseOver = CheckCollisionPointRec(mouseWorldPosition, rect); !isMouseOver)
    {
        DrawRectangleRec(rect, {230, 230, 230, 255});
        DrawTextCentered(rect, font, text, fontSize, {25, 25, 25, 255});
        return false;
    }

    const Color color = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? Color{160, 160, 160, 255} : Color{190, 190, 190, 255};
    DrawRectangleRec(rect, color);
    DrawTextCentered(rect, font, text, fontSize, {
                         static_cast<unsigned char>(255 - color.r),
                         static_cast<unsigned char>(255 - color.g),
                         static_cast<unsigned char>(255 - color.b),
                         255
                     });


    return IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
}

void MainMenuSystem::Update(GameSystemsUpdateArgs& args) const
{
    const auto& view = args.Registry.view<MainMenuComponent, RendererComponent>();
    for (const auto& entity : view)
    {
        auto& mainMenu = view.get<MainMenuComponent>(entity);
        auto& renderer = view.get<RendererComponent>(entity);
        const auto width = static_cast<float>(GetScreenWidth());
        const auto height = static_cast<float>(GetScreenHeight());
        const SpriteData sprite = args.Assets.Sprites.FromId(renderer.Data.Sprite);
        const Texture2D tex = sprite.Tex;

        if (!IsTextureValid(tex))
            continue;

        const float scale = renderer.Data.LocalScale = std::min(width / static_cast<float>(tex.width),
                                                                height / static_cast<float>(tex.height));


        const Rectangle menuRect = {
            renderer.Data.Position.Value.x - sprite.Pivot.x * scale,
            renderer.Data.Position.Value.y - sprite.Pivot.y * scale,
            660 * scale,
            height
        };

        //DrawRectangleRec(menuRect, {255, 100, 100, 120});
        const Font font = args.Assets.Text.Font;
        const float fontSize = 64 * scale;
        DrawTextEx(font, "Sheep", {menuRect.x + 250 * scale, menuRect.y + 50 * scale}, fontSize, 1,
                   BLACK);
        DrawTextEx(font, "Goes", {menuRect.x + 290 * scale, menuRect.y + 80 * scale}, fontSize, 1, BLACK);
        DrawTextEx(font, "Devile", {menuRect.x + 250 * scale, menuRect.y + 110 * scale}, fontSize, 1,
                   RED);

        const float btnPadding = 50 * scale;
        const float btnHeight = 100 * scale;

        Rectangle btnRect = {
            menuRect.x + btnPadding, menuRect.y + 300 * scale, 660 * scale - btnPadding - btnPadding, btnHeight
        };

        switch (mainMenu.CurrentPanel)
        {
            case MainMenuComponent::Panel::MainMenu:
                if (Button(btnRect, args.Assets.Text.MainMenu.Play.c_str(), fontSize, font, args.MouseWorldPosition))
                {
                    args.Assets.Levels.Load(2137);;
                }

                btnRect.y += btnHeight + btnPadding;

                if (Button(btnRect, args.Assets.Text.MainMenu.Settings.c_str(), fontSize, font,
                           args.MouseWorldPosition))
                {
                    mainMenu.CurrentPanel = MainMenuComponent::Panel::Settings;
                }
                btnRect.y += btnHeight + btnPadding;

                if (Button(btnRect, args.Assets.Text.MainMenu.Credits.c_str(), fontSize, font, args.MouseWorldPosition))
                {
                    mainMenu.CurrentPanel = MainMenuComponent::Panel::Credits;
                }
                btnRect.y += btnHeight + btnPadding;

                if (Button(btnRect, args.Assets.Text.MainMenu.Exit.c_str(), fontSize, font, args.MouseWorldPosition))
                {
                    CloseWindow();
                }
                break;
            case MainMenuComponent::Panel::Settings:
                if constexpr (const Rectangle langRect = {
                    btnRect.x + btnRect.height + btnPadding, btnRect.y,
                    btnRect.width - btnRect.height - btnRect.height - btnPadding - btnPadding, btnRect.height
                }; true)
                {
                    DrawRectangleRec(langRect, {255, 255, 255, 255});
                    DrawTextCentered(langRect, font,
                                     args.Assets.Text.Languages.Value[static_cast<int>(args.Assets.Text.
                                         CurrentLanguage)].c_str(), fontSize, {25, 25, 25, 255});
                }

                if (Button({btnRect.x, btnRect.y, btnRect.height, btnRect.height}, "<", fontSize, font,
                           args.MouseWorldPosition))
                {
                    const auto lang = static_cast<Language>(
                        std::abs(static_cast<int>(args.Assets.Text.CurrentLanguage) - 1) % static_cast<int>(
                            Language::COUNT));
                    args.Assets.Text.LoadAll(lang);
                }


                if (Button({btnRect.x + btnRect.width - btnRect.height, btnRect.y, btnRect.height, btnRect.height}, ">",
                           fontSize, font,
                           args.MouseWorldPosition))
                {
                    const auto lang = static_cast<Language>(
                        (static_cast<int>(args.Assets.Text.CurrentLanguage) + 1) % static_cast<int>(Language::COUNT));
                    args.Assets.Text.LoadAll(lang);
                }

                btnRect.y += (btnHeight + btnPadding) * 3;
                if (Button(btnRect, args.Assets.Text.MainMenu.Back.c_str(), fontSize, font, args.MouseWorldPosition))
                {
                    mainMenu.CurrentPanel = MainMenuComponent::Panel::MainMenu;
                }
                break;
            case MainMenuComponent::Panel::Credits:
                DrawTextEx(font, "SoMakeAWish", {btnRect.x, btnRect.y}, fontSize, 1, {25, 25, 25, 255});
                DrawTextEx(font, "Pilmincia", {btnRect.x, btnRect.y + 100 * scale}, fontSize, 1, {25, 25, 25, 255});
                btnRect.y += (btnHeight + btnPadding) * 3;
                if (Button(btnRect, args.Assets.Text.MainMenu.Back.c_str(), fontSize, font, args.MouseWorldPosition))
                {
                    mainMenu.CurrentPanel = MainMenuComponent::Panel::MainMenu;
                }
                break;
        }
    }
}
