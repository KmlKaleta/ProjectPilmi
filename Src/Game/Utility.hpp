//
// Created by Kamil on 30.05.2026.
//

#ifndef SHEEP_GOES_DEVILE_UTILITY_H
#define SHEEP_GOES_DEVILE_UTILITY_H

#include <string>

inline uint64_t StringToHash(const std::string& str)
{
    uint64_t hash = 14695981039346656037ull;

    for (const char c : str)
    {
        hash ^= static_cast<uint8_t>(c);
        hash *= 1099511628211ull;
    }

    return hash;
}

#endif //SHEEP_GOES_DEVILE_UTILITY_H
