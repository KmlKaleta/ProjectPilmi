//
// Created by Kamil on 11.07.2026.
//

#ifndef SHEEP_GOES_DEVILE_LOCATION_EDITOR_WINDOW_H
#define SHEEP_GOES_DEVILE_LOCATION_EDITOR_WINDOW_H
#include "TextManager.h"

struct LocationEditorWindow
{
    TextManager Texts[static_cast<int>(Language::COUNT)];

    bool Init();

    bool Update();

    void Close();
};

#endif //SHEEP_GOES_DEVILE_LOCATION_EDITOR_WINDOW_H
