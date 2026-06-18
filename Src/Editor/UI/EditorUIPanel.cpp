//
// Created by Kamil on 17.06.2026.
//
#include "EditorUIPanel.h"
#include "raygui.h"

Color BaseColor()
{
    return GetColor(GuiGetStyle(BUTTON, BASE_COLOR_NORMAL));
}

Color BorderColor()
{
    return GetColor(GuiGetStyle(BUTTON, BORDER_COLOR_NORMAL));
}

void EditorUIPanel::DrawPanel(const Rectangle size, const float border)
{
    DrawRectangleRec(size, BaseColor());
    DrawRectangleLinesEx(size, border, BorderColor());
}
