//
// Created by Kamil on 27.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_STRING_UTILITY_HPP
#define SHEEP_GOES_DEVILE_STRING_UTILITY_HPP
#include <string>

inline bool IsNullOrWhiteSpace(const std::string& s)
{
    return s.empty() ||
           std::all_of(s.begin(), s.end(),
                       [](const unsigned char c)
                       {
                           return std::isspace(c);
                       });
}

#endif //SHEEP_GOES_DEVILE_STRING_UTILITY_HPP
