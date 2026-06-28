//
// Created by Kamil on 28.06.2026.
//
#include "EditorSystems.h"

void EditorSystems::Update(GameSystemsUpdateArgs& args)
{
#define X(t) t##Instance.Update(args);
    EditorSystemsMacro(X)
#undef X
}
