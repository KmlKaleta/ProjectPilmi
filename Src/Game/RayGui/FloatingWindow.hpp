//
// Created by Kamil on 03.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_FLOATING_WINDOW_H
#define SHEEP_GOES_DEVILE_FLOATING_WINDOW_H
#include "raylib.h"
#include "raygui.h"

struct FloatingWindow
{
    Vector2 Position = {10, 10};
    Vector2 Size = {200, 400};
    bool Minimized = false;
    bool Moving = false;
    bool Resizing = false;
    bool Scissor = false;
    Vector2 Scroll = {};

#if !defined(RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT)
#define RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT 24
#endif

#if !defined(RAYGUI_WINDOW_CLOSEBUTTON_SIZE)
#define RAYGUI_WINDOW_CLOSEBUTTON_SIZE 18
#endif

    void Update()
    {
        constexpr int close_title_size_delta_half =
                (RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT - RAYGUI_WINDOW_CLOSEBUTTON_SIZE) / 2;

        // window movement and resize input and collision check
        Vector2 mouse = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !Moving && !Resizing)
        {
            Rectangle title_collision_rect = {
                Position.x, Position.y, Size.x - (RAYGUI_WINDOW_CLOSEBUTTON_SIZE + close_title_size_delta_half),
                RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT
            };
            Rectangle resize_collision_rect = {Position.x + Size.x - 20, Position.y + Size.y - 20, 20, 20};

            if (CheckCollisionPointRec(mouse, title_collision_rect))
            {
                Moving = true;
            } else if (!Minimized && CheckCollisionPointRec(mouse, resize_collision_rect))
            {
                Resizing = true;
            }
        }

        // window movement and resize update
        if (Moving)
        {
            Vector2 mouse_delta = GetMouseDelta();
            Position.x += mouse_delta.x;
            Position.y += mouse_delta.y;

            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
            {
                Moving = false;

                // clamp window position keep it inside the application area
                if (Position.x < 0) Position.x = 0;
                else if (Position.x > GetScreenWidth() - Size.x) Position.x = GetScreenWidth() - Size.x;
                if (Position.y < 0) Position.y = 0;
                else if (Position.y > GetScreenHeight())
                    Position.y = GetScreenHeight() - RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT;
            }
        } else if (Resizing)
        {
            if (mouse.x > Position.x)
                Size.x = mouse.x - Position.x;
            if (mouse.y > Position.y)
                Size.y = mouse.y - Position.y;

            // clamp window size to an arbitrary minimum value and the window size as the maximum
            if (Size.x < 200) Size.x = 200;
            else if (Size.x > GetScreenWidth()) Size.x = GetScreenWidth();
            if (Size.y < 200) Size.y = 200;
            else if (Size.y > GetScreenHeight()) Size.y = GetScreenHeight();

            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
            {
                Resizing = false;
            }
        }
    }

    Vector2 ContentStart()
    {
        return  {Position.x + Scroll.x, Position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT + Scroll.y};
    }

    bool StartDrawing(const char* title, Rectangle content)
    {
        constexpr int close_title_size_delta_half =
                (RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT - RAYGUI_WINDOW_CLOSEBUTTON_SIZE) / 2;
        // window and content drawing with scissor and scroll area
        if (Minimized)
        {
            GuiStatusBar((Rectangle){Position.x, Position.y, Size.x, RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT}, title);

            if (GuiButton((Rectangle){
                              Position.x + Size.x - RAYGUI_WINDOW_CLOSEBUTTON_SIZE - close_title_size_delta_half,
                              Position.y + close_title_size_delta_half,
                              RAYGUI_WINDOW_CLOSEBUTTON_SIZE,
                              RAYGUI_WINDOW_CLOSEBUTTON_SIZE
                          },
                          "#120#"))
            {
                Minimized = false;
            }
            return false;
        }

        Minimized = GuiWindowBox((Rectangle){Position.x, Position.y, Size.x, Size.y}, title);

        Rectangle scissor = {};
        float heightBounds = Size.y - RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT;
        GuiScrollPanel((Rectangle){
                           Position.x, Position.y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT, Size.x,
                           heightBounds
                       },
                       nullptr,
                       content,
                       &Scroll,
                       &scissor);

        Scissor = Size.x < content.width || heightBounds < content.height;

        if (Scissor)
        {
            BeginScissorMode(scissor.x, scissor.y, scissor.width, scissor.height);
        }

        // draw the resize button/icon
        GuiDrawIcon(71, Position.x + Size.x - 20, Position.y + Size.y - 20, 1, WHITE);
        return true;
    }

    void EndDrawing()
    {
        if (Scissor)
        {
            EndScissorMode();
        }
    }
};

#endif //SHEEP_GOES_DEVILE_FLOATING_WINDOW_H
