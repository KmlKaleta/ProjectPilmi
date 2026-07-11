//
// Created by Kamil on 07.07.2026.
//
#include "EntitySelection.h"

#include "raylib.h"
#include "UndoRecorder.hpp"

void EntitySelection::HandleInputs(EntityStorage& storage, EditorUndoRedo& undoRedo)
{
    if (IsKeyPressed(KEY_DELETE))
    {
        RecordEntityDeletion(undoRedo, storage, *this);
    }
}
