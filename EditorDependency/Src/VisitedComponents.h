//
// Created by Kamil on 27.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_VISITED_COMPONENTS_H
#define SHEEP_GOES_DEVILE_VISITED_COMPONENTS_H
#include "Renderer.h"
#include "Fields/WorldPosition.hpp"
#include "include/visit_struct/visit_struct.hpp"

VISITABLE_STRUCT(Renderer, Sprite, Position, LocalScale, Flip, TexX, TexY);
VISITABLE_STRUCT(WorldPosition, Value, Anchor);
#endif //SHEEP_GOES_DEVILE_VISITED_COMPONENTS_H
