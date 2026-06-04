//
// Created by Kamil on 03.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_EDITOR_RENDERERS_H
#define SHEEP_GOES_DEVILE_EDITOR_RENDERERS_H
#include <vector>
#include <raylib.h>

struct Renderer;
struct SpriteManager;

struct EditorRenderers
{
    size_t SelectedRenderer;
    bool AnySelected = false;

    std::vector<size_t> RenderersToSelect = {};
    bool RendererSelection = false;
    Vector2 SelectionClickPosition;

    int DragType = 0;
    Vector2 DragOffset;

    enum
    {
        DRAG_NONE = 0,
        DRAG_FREE,
        DRAG_X,
        DRAG_Y
    };

    void DrawBoundsOnly(const std::vector<Renderer>& renderers, const SpriteManager& sprites);

    void HandleSelection(Vector2 mousePosition, bool canInteract, std::vector<Renderer>& renderers,
                         const SpriteManager& sprites);

    void Update(Vector2 mousePosition, bool canInteract, std::vector<Renderer>& renderers,
                const SpriteManager& sprites);
};

#endif //SHEEP_GOES_DEVILE_EDITOR_RENDERERS_H
