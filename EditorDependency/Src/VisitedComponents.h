//
// Created by Kamil on 27.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_VISITED_COMPONENTS_H
#define SHEEP_GOES_DEVILE_VISITED_COMPONENTS_H
#include "Components.h"
#include "include/visit_struct/visit_struct.hpp"

// components
VISITABLE_STRUCT(ParallaxComponent, Strength);
VISITABLE_STRUCT(EntityGroupComponent, Entities);
VISITABLE_STRUCT(EntityGroupChildComponent, Value);
VISITABLE_STRUCT(OrderComponent, Value);
VISITABLE_STRUCT(RendererComponent, LayerOrder, Data);
VISITABLE_STRUCT(MoveSpeedComponent, Value);
VISITABLE_STRUCT(PatrolComponent, From, To, Reversed);
VISITABLE_STRUCT(RoundComponent, Center, Radius);
VISITABLE_STRUCT(AnimatorComponent, Animation, FrameTime);
VISITABLE_STRUCT(MainMenuComponent, CurrentPanel);
VISITABLE_STRUCT(TextComponent, Position, FontSize, Value);

// other
VISITABLE_STRUCT(Renderer, Sprite, Position, LocalScale, Flip, TexX, TexY);
VISITABLE_STRUCT(WorldPosition, Value, Anchor);
#endif //SHEEP_GOES_DEVILE_VISITED_COMPONENTS_H
