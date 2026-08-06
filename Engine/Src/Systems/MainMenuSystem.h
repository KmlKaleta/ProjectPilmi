//
// Created by Kamil on 09.07.2026.
//

#ifndef SHEEP_GOES_DEVILE_MAIN_MENU_SYSTEM_H
#define SHEEP_GOES_DEVILE_MAIN_MENU_SYSTEM_H
#include "Components.h"

struct GameSystemsUpdateArgs;

struct MainMenuSystem
{
    bool isHovered[6] = {};

    void SetMenuPanel(MainMenuComponent& mainMenu, MainMenuComponent::Panel panel);

    void Update(GameSystemsUpdateArgs& args);
};

#endif //SHEEP_GOES_DEVILE_MAIN_MENU_SYSTEM_H
