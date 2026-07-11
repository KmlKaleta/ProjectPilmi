//
// Created by Kamil on 28.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_EDITOR_SYSTEMS_H
#define SHEEP_GOES_DEVILE_EDITOR_SYSTEMS_H

#include "Systems/RenderingSystem.h"
#include "PatrolVisualizationSystem.h"
#include "RoundVisualizationSystem.h"
#include "Systems/MainMenuSystem.h"
#include "Systems/ParallaxSystem.h"
#include "Systems/ScaleToScreenSystem.h"

#define EditorSystemsMacro(X) \
    X(ParallaxSystem) \
    X(RenderingSystem) \
    X(PatrolVisualizationSystem) \
    X(RoundVisualizationSystem) \
    X(ScaleToScreenSystem) \
    X(MainMenuSystem)

struct GameSystemsUpdateArgs;

struct EditorSystems
{
#define X(t) t t##Instance;
    EditorSystemsMacro(X)
#undef X
    void Update(GameSystemsUpdateArgs& args);
};


#endif //SHEEP_GOES_DEVILE_EDITOR_SYSTEMS_H
