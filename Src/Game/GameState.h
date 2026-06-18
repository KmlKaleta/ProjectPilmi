//
// Created by Kamil on 10.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_GAME_INTERACTION_H
#define SHEEP_GOES_DEVILE_GAME_INTERACTION_H
#include "Editor/EditorFields.h"

// struct GameEvent
// {
//     int Type;
//     int DataIndex;
//
//     enum
//     {
//         INIT = 0,
//         UPDATE,
//
//         COUNT
//     };
// };
//
// struct Condition
// {
//     int Type;
//     int DataIndex;
// };

struct PatrolState
{
    EntitySelector Entity;
    Vector2Selector PositionA;
    Vector2Selector PositionB;
};

struct GameState
{
    int Type;
    int DataIndex;

    enum
    {
        SET_POSITION = 0,
        MOVE_TO,

        COUNT
    };
};

#endif //SHEEP_GOES_DEVILE_GAME_INTERACTION_H
