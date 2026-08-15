//
// Created by Kamil on 14.08.2026.
//

#ifndef SHEEP_GOES_DEVILE_FIXED_FRAMERATE_60FPS_H
#define SHEEP_GOES_DEVILE_FIXED_FRAMERATE_60FPS_H

struct FixedFrameRate60FPS
{
    constexpr static float fixedDeltaTime = 1.0f / 60.0f;

    void Update(const float deltaTime)
    {
        _accumulator += deltaTime;
    }

    bool Step()
    {
        if (_accumulator >= fixedDeltaTime)
        {
            _accumulator -= fixedDeltaTime;
            return true;
        }
        return false;
    }

private:
    float _accumulator = 0.0f;
};
#endif //SHEEP_GOES_DEVILE_FIXED_FRAMERATE_60FPS_H
