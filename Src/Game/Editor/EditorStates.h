//
// Created by Kamil on 10.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_EDITOR_ACTIONS_H
#define SHEEP_GOES_DEVILE_EDITOR_ACTIONS_H
#include <cstddef>

struct LevelData;
struct Vector2;

struct EditorStates
{
    size_t SelectedState = 0;
    bool AnySelected = false;

    void Update(Vector2 vector2, bool canInteract, LevelData& levelData);
};

#endif //SHEEP_GOES_DEVILE_EDITOR_ACTIONS_H
