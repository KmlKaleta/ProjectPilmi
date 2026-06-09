//
// Created by Kamil on 09.06.2026.
//
#include "EditorFields.h"

Range::Range(const float min, const float max, const float value) : Min(min), Max(max), Value(value)
{
    Sanitize();
}

void Range::Sanitize()
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

float Range::Get() const
{
    return Value;
}

float Range::Set(const float newValue)
{
    Value = newValue;
    Sanitize();
    return Value;
}

void to_json(JSON& j, const Range& r)
{
    j = r.Get();
}

void from_json(const JSON& j, Range& r)
{
    r.Set(j.get<float>());
}
