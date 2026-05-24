#pragma once
#include <raylib.h>
#include <vector>
#include "AnimationData.h"
#include "SpriteData.h"
#include <assert.h>

struct AnimationTexture
{
    SpriteData Sprite;
    float FrameWidth = 100;
    float FrameHeight = 100;

    std::vector<int> FramesPerAnimation = {1};

    void Load(const char *path, float scale, Vector2 pivot, int frameCount, int animationCount, std::vector<int> framesPerAnimation)
    {
        assert(frameCount != 0 && animationCount != 0);

        Sprite.Load(path, scale, pivot);
        FramesPerAnimation = framesPerAnimation;
        FrameWidth = Sprite.Tex.width / frameCount;
        FrameHeight = Sprite.Tex.height / animationCount;
    }

    void Render(Vector2 position, AnimationData data, bool flipped)
    {
        int flip = flipped ? -1 : 1;
        Sprite.Render(position, {data.Frame * FrameWidth, data.Animation * FrameHeight, FrameWidth * flip, FrameHeight});
    }
};
