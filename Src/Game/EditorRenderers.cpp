//
// Created by Kamil on 03.06.2026.
//
#include "EditorRenderers.h"

#include "raygui.h"
#include "Renderer.h"
#include "SpriteManager.h"

void EditorRenderers::DrawBoundsOnly(const std::vector<Renderer>& renderers, const SpriteManager& sprites)
{
    for (size_t i = 0; i < renderers.size(); ++i)
    {
        const Renderer& renderer = renderers[i];
        const Color color = AnySelected && i == SelectedRenderer ? YELLOW : GREEN;
        const Rectangle renderBounds = renderer.GetBounds(sprites);
        DrawRectangleLinesEx(renderBounds, 1, color);
    }
}

void EditorRenderers::HandleSelection(const Vector2 mousePosition, const bool canInteract,
                                      std::vector<Renderer>& renderers, const SpriteManager& sprites)
{
    RenderersToSelect.clear();
    for (size_t i = 0; i < renderers.size(); ++i)
    {
        Renderer& renderer = renderers[i];
        const Rectangle renderBounds = renderer.GetBounds(sprites);

        Color color = AnySelected && i == SelectedRenderer ? YELLOW : GREEN;

        if (!canInteract)
        {
            goto Draw;
        }

        if (CheckCollisionPointRec(mousePosition, renderBounds))
        {
            color = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? Color{190, 20, 20, 255} : RED;
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            {
                RenderersToSelect.push_back(i);
            }
        }

    Draw:
        DrawRectangleLinesEx(renderBounds, 1, color);
    }

    if (RenderersToSelect.empty())
    {
        return;
    }

    if (RenderersToSelect.size() == 1)
    {
        SelectedRenderer = RenderersToSelect[0];
        AnySelected = true;
        return;
    }

    RendererSelection = true;
    SelectionClickPosition = GetMousePosition();
}

void EditorRenderers::Update(const Vector2 mousePosition, const bool canInteract, std::vector<Renderer>& renderers,
                             const SpriteManager& sprites)
{
    if (RendererSelection)
    {
        return;
    }

    if (!AnySelected)
    {
        HandleSelection(mousePosition, canInteract, renderers, sprites);
        return;
    }

    Renderer& renderer = renderers[SelectedRenderer];
    const SpriteData selectedSprite = sprites.FromId(renderer.Sprite);
    const Vector2 handlePosition = renderer.Position - selectedSprite.Pivot * renderer.LocalScale;
    const Vector2 yHandlePosition = handlePosition + Vector2{35, 0};
    const Vector2 xHandlePosition = handlePosition + Vector2{0, 35};

    bool freeHandle = CheckCollisionPointCircle(mousePosition, handlePosition, 10);
    bool xHandle = CheckCollisionPointCircle(mousePosition, xHandlePosition, 10);
    bool yHandle = CheckCollisionPointCircle(mousePosition, yHandlePosition, 10);

    const bool handleUnderCursor = DragType != 0 || freeHandle || xHandle || yHandle;
    if (!handleUnderCursor)
    {
        HandleSelection(mousePosition, canInteract, renderers, sprites);
    } else
    {
        DrawBoundsOnly(renderers, sprites);
    }

    switch (DragType)
    {
        case DRAG_X:
            renderer.Position.x = mousePosition.x - DragOffset.x + selectedSprite.Pivot.x * renderer.LocalScale;
            break;
        case DRAG_Y:
            renderer.Position.y = mousePosition.y - DragOffset.y + selectedSprite.Pivot.y * renderer.LocalScale;
            break;
        case DRAG_FREE:
            renderer.Position = mousePosition - DragOffset + selectedSprite.Pivot * renderer.LocalScale;
            break;
        default:
            break;
    }

    DrawCircle(handlePosition.x, handlePosition.y, 10,
               freeHandle ? Color{60, 60, 160, 255} : Color{100, 100, 230, 255});
    DrawCircle(xHandlePosition.x, xHandlePosition.y, 10, xHandle ? Color{160, 60, 60, 255} : Color{230, 100, 100, 255});
    DrawCircle(yHandlePosition.x, yHandlePosition.y, 10, yHandle ? Color{60, 160, 60, 255} : Color{100, 230, 100, 255});

    if (handleUnderCursor && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (xHandle)
        {
            DragType = DRAG_X;
            DragOffset = mousePosition - xHandlePosition;
        }

        if (yHandle)
        {
            DragType = DRAG_Y;
            DragOffset = mousePosition - yHandlePosition;
        }

        if (freeHandle)
        {
            DragType = DRAG_FREE;
            DragOffset = mousePosition - handlePosition;
        }
    }

    if (handleUnderCursor && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        DragType = 0;
    }
}
