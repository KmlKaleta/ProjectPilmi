#pragma once
#include "AnimationTexture.h"
#include "SpriteData.h"
#include "SpriteAtlas.h"

struct AssetManager
{
    Texture2D Atlas;
    Texture2D Frame;

    enum SpriteType
    {
        SPRITE_GRASS = 0,
        SPRITE_TREE1,
        SPRITE_TREE2,
        SPRITE_CLOUD_BACKGROUND,

        SPRITE_COUNT
    };

    enum AtlasType
    {
        ATLAS_FLOWER = 0,

        ATLAS_COUNT
    };

    enum AnimationType
    {
        ANIMATION_BEESHOP = 0,
        ANIMATION_NUN,
        ANIMATION_BUNERO,

        ANIMATION_COUNT
    };

    SpriteData Sprites[SPRITE_COUNT] = {};
    SpriteAtlas Atlases[ATLAS_COUNT] = {};
    AnimationTexture Animations[ANIMATION_COUNT] = {};

    void LoadAll();
};