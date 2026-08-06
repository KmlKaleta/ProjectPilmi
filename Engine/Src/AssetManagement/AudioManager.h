//
// Created by Kamil on 13.07.2026.
//

#ifndef SHEEP_GOES_DEVILE_AUDIO_MANAGER_H
#define SHEEP_GOES_DEVILE_AUDIO_MANAGER_H
#include "raylib.h"

struct AudioManager
{
    Sound Hover{};
    Sound Click{};
    Music MenuMusic{};

    void LoadAll();
};

#endif //SHEEP_GOES_DEVILE_AUDIO_MANAGER_H
