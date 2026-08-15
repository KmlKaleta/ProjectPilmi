//
// Created by Kamil on 07.08.2026.
//

#ifndef SHEEP_GOES_DEVILE_PLAYER_MOVEMENT_SYSTEM_H
#define SHEEP_GOES_DEVILE_PLAYER_MOVEMENT_SYSTEM_H
struct GameSystemsUpdateArgs;

struct PlayerMovementSystem
{
    void Update(GameSystemsUpdateArgs& args) const;
};
#endif //SHEEP_GOES_DEVILE_PLAYER_MOVEMENT_SYSTEM_H
