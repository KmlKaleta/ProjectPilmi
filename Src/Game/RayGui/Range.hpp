//
// Created by Kamil on 07.06.2026.
//
#pragma once
#include <raylib.h>
#include <raygui.h>

void FloatSlider(Rectangle rect, float& value, const float min, const float max, const float padding = 5)
{
    if (GuiButton({rect.x, rect.y, 20, rect.height}, "#118#"))
    {
        value -= 0.01f;
    }

    rect.x += 20 + padding;
    const float sliderWidth = rect.width - padding - 50;
    GuiSlider({rect.x, rect.y, sliderWidth, rect.height}, "", "", &value, min, max);
    rect.x += sliderWidth + padding;

    if (GuiButton({rect.x, rect.y, 20, rect.height}, "#119#"))
    {
        value += 0.01f;
    }
}

void IntField(Rectangle rect, int& value, const char* name, const float padding = 5)
{
    const auto nameWidth = static_cast<float>(MeasureText(name, 20));

    GuiLabel({rect.x, rect.y, nameWidth, rect.height}, name);

    rect.x += nameWidth + padding;

    if (GuiButton({rect.x, rect.y, 20, rect.height}, "#118#"))
    {
        value--;;
    }

    rect.x += 20 + padding;

    GuiLabel({
                 rect.x, rect.y, 50, rect.height
             }, TextFormat("%i", value));

    rect.x += 50 + padding;

    if (GuiButton({rect.x, rect.y, 20, rect.height}, "#119#"))
    {
        value++;
    }
}