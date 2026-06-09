//
// Created by Kamil on 03.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_EDITOR_RENDERERS_H
#define SHEEP_GOES_DEVILE_EDITOR_RENDERERS_H
#include <vector>
#include <raylib.h>

struct Renderer;
struct SpriteManager;
struct LevelData;

struct EditorRenderers
{
    bool AnySelected = false;

    std::vector<size_t> RenderersToSelect = {};
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

    void DrawBoundsOnly(LevelData& levelData, const SpriteManager& sprites) const;

    void HandleSelection(Vector2 mousePosition, bool canInteract, LevelData& levelData, const SpriteManager& sprites);

    void Update(Vector2 mousePosition, bool canInteract, LevelData& levelData, const SpriteManager& sprites);

    void SelectRenderer(size_t index);

    size_t GetSelectedRenderer() const;

    bool IsSelectionPhase() const;

    void CancelSelection();

private:
    size_t SelectedRenderer = 0;
    bool RendererSelection = false;
};

#endif //SHEEP_GOES_DEVILE_EDITOR_RENDERERS_H
