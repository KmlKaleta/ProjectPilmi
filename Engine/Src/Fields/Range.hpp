//
// Created by Kamil on 23.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_RANGE_HPP
#define SHEEP_GOES_DEVILE_RANGE_HPP
#include "JSON.h"

template<typename T>
struct Range
{
    T Min = 0;
    T Max = 1;

    Range() = default;

    Range(const T min, const T max, const T value) : Min(min), Max(max), Value(value)
    {
        Sanitize();
    }

    void Sanitize()
    {
        if (Value > Max)
        {
            Value = Max;
        }

        if (Value < Min)
        {
            Value = Min;
        }
    }

    T Get() const
    {
        return Value;
    }

    T Set(const float newValue)
    {
        Value = newValue;
        Sanitize();
        return Value;
    }

private:
    float Value = Min;
};

template<typename T>
void to_json(JSON& j, const Range<T>& r)
{
    j = r.Get();
}

template<typename T>
void from_json(const JSON& j, Range<T>& r)
{
    r.Set(j.get<float>());
}

#endif //SHEEP_GOES_DEVILE_RANGE_HPP
