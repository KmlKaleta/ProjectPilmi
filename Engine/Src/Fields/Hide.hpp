//
// Created by Kamil on 13.07.2026.
//

#ifndef SHEEP_GOES_DEVILE_HIDE_HPP
#define SHEEP_GOES_DEVILE_HIDE_HPP
#include "JSON.h"

template<typename T>
struct Hide
{
    T Value;

    Hide() = default;

    Hide(const T& value) : Value(value)
    {
    }

    operator T() const
    {
        return Value;
    }

    Hide& operator=(const T& value)
    {
        Value = value;
        return *this;
    }
};

template <typename T>
struct is_hide : std::false_type {};

template <typename U>
struct is_hide<Hide<U>> : std::true_type {};

template<typename  T>
void to_json(JSON& j, const Hide<T>& h)
{
    j = h.Value;
}

template<typename  T>
void from_json(const JSON& j, Hide<T>& h)
{
    h.Value = j;
}

#endif //SHEEP_GOES_DEVILE_HIDE_HPP
