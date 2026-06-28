//
// Created by Kamil on 27.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_SPRITE_SELECTOR_H
#define SHEEP_GOES_DEVILE_SPRITE_SELECTOR_H
#include "UUID.hpp"

struct SpriteSelector
{
    UUID Id;

    operator UUID() const { return Id; }
};
#endif //SHEEP_GOES_DEVILE_SPRITE_SELECTOR_H
