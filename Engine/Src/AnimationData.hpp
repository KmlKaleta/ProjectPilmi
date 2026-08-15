#pragma once
#include "JSON.h"

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

inline void to_json(JSON& j, const AnimationData& data)
{
    j["t"] = data.T;
    j["t_max"] = data.TMax;
    j["frame"] = data.Frame;
    j["animation"] = data.Animation;
}

inline void from_json(const JSON& j, AnimationData& data)
{
    ReadJsonValue(data.T, j, "t", data.T);
    ReadJsonValue(data.TMax, j, "t_max", data.TMax);
    ReadJsonValue(data.Frame, j, "frame", data.Frame);
    ReadJsonValue(data.Animation, j, "animation", data.Animation);
}
