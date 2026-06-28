#pragma once

struct AnimationData
{
    float T = 0;
    float TMax = 0.1f;

    int Frame = 0;

    int Animation = 0;

    void Update(const float deltaTime, const int frameCount)
    {
        T += deltaTime;
        while (T >= TMax)
        {
            T -= TMax;
            Frame = (Frame + 1) % frameCount;
        }
    }

    void SetAnimation(const int animation)
    {
        if (Animation == animation)
        {
            return;
        }

        Frame = 0;
        Animation = animation;
    }
};
