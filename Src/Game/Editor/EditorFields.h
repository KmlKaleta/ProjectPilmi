//
// Created by Kamil on 09.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_EDITOR_FIELDS_H
#define SHEEP_GOES_DEVILE_EDITOR_FIELDS_H
#include "JSON.h"

struct Range
{
    float Min = 0;
    float Max = 1;

    Range(float min, float max, float value = 1);

    void Sanitize();

    float Get() const;

    float Set(float newValue);
private:
    float Value = Min;
};

void to_json(JSON& j, const Range& r);

void from_json(const JSON& j, Range& r);

#endif //SHEEP_GOES_DEVILE_EDITOR_FIELDS_H
