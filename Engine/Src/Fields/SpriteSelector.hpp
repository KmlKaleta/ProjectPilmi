//
// Created by Kamil on 27.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_SPRITE_SELECTOR_H
#define SHEEP_GOES_DEVILE_SPRITE_SELECTOR_H
#include "UUID.hpp"

struct SpriteSelector
{
    UUID Id;

    SpriteSelector() = default;

    operator UUID() const
    {
        JSON x;
        return Id;
    }
};

inline void to_json(JSON& j, const SpriteSelector& selector)
{
    j = selector.Id;
}

inline void from_json(const JSON& j, SpriteSelector& selector)
{
    ReadJsonValue(selector.Id, j, UUID());
}


#endif //SHEEP_GOES_DEVILE_SPRITE_SELECTOR_H
