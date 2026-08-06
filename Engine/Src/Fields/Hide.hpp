//
// Created by Kamil on 13.07.2026.
//

#ifndef SHEEP_GOES_DEVILE_HIDE_HPP
#define SHEEP_GOES_DEVILE_HIDE_HPP

template<typename T>
struct Hide
{
    T Value;

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

#endif //SHEEP_GOES_DEVILE_HIDE_HPP
