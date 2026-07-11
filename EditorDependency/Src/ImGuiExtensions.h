//
// Created by Kamil on 24.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_IM_GUI_EXTENSIONS_H
#define SHEEP_GOES_DEVILE_IM_GUI_EXTENSIONS_H
#include "Fields/WorldPosition.hpp"

struct Renderer;
struct SpriteData;
struct SpriteManager;

namespace ImGui
{
    void DockingSetup();

    // void WorldPositionEdit(const char* label, WorldPosition* position);
    //
    // void RendererEdit(const char* label, Renderer* renderer, const SpriteManager& sprites);
    //
    // void SpriteDataEdit(const char* label, SpriteData* spriteData);
}

#endif //SHEEP_GOES_DEVILE_IM_GUI_EXTENSIONS_H
