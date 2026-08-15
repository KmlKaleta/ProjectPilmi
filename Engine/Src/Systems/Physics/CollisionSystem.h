//
// Created by Kamil on 28.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_COLLISION_SYSTEM_H
#define SHEEP_GOES_DEVILE_COLLISION_SYSTEM_H
struct GameSystemsUpdateArgs;

struct CollisionSystem
{
    void Update(GameSystemsUpdateArgs& args) const;
};
#endif //SHEEP_GOES_DEVILE_COLLISION_SYSTEM_H
