#include "SpriteData.h"
#include "SpriteAtlas.h"
#include "AnimationTexture.h"
#include "SpriteData.h"
#include <vector>

struct SpriteGeneric
{
    SpriteData &Sprite;

    float width = 100;
    float height = 100;

    std::vector<int> RowCounts = {1};

    int Type;

    void Raw(SpriteData raw)
    {
        Type = SPRITE_TYPE_RAW;
        width = raw.Tex.width;
        height = raw.Tex.height;
        RowCounts = {1};
    }

    void Atlas(SpriteAtlas atlas)
    {
        Type = SPRITE_TYPE_Atlas;
        width = atlas.SpriteWidth;
        height = atlas.SpriteHeight;
        RowCounts = {};
        RowCounts.resize(atlas.SpritesY);
        for (int y = 0; y < atlas.SpritesY; y++)
        {
            RowCounts[y] = atlas.SpritesX;
        }
    }

    void Animation(AnimationTexture anim)
    {
        Type = SPRITE_TYPE_Animation;
        width = anim.FrameWidth;
        height = anim.FrameHeight;
        RowCounts = anim.FramesPerAnimation;
    }

    void Render(Vector2 position, int column, int row, bool flip)
    {
        SpriteAtlas atlas = {Sprite, RowCounts.size(), RowCounts[0], width, height};
        AnimationTexture anim{Sprite, width, height, RowCounts};
        AnimationData data = {};

        switch (Type)
        {
        case SPRITE_TYPE_RAW:
            Sprite.Render(position);
            break;
        case SPRITE_TYPE_Atlas:
            atlas.Render(position, column, row);
            break;
        case SPRITE_TYPE_Animation:
            data.Frame = column;
            data.Animation = row;
            anim.Render(position, data, flip);
            break;
        default:
            break;
        }
    }

    enum
    {
        SPRITE_TYPE_RAW,
        SPRITE_TYPE_Atlas,
        SPRITE_TYPE_Animation
    };
};
