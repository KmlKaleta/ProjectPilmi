//
// Created by Kamil on 22.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_ENTITY_SELECTION_H
#define SHEEP_GOES_DEVILE_ENTITY_SELECTION_H
#include "UUID.hpp"

struct EntityStorage;
struct EditorUndoRedo;

struct EntitySelection
{
    UUID SelectedEntity = 0;

    void HandleInputs(EntityStorage& storage, EditorUndoRedo& undoRedo);
};
#endif //SHEEP_GOES_DEVILE_ENTITY_SELECTION_H
