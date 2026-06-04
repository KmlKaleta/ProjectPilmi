//
// Created by Kamil on 30.05.2026.
//

#ifndef SHEEP_GOES_DEVILE_UTILITY_H
#define SHEEP_GOES_DEVILE_UTILITY_H

#include <string>
#include <fstream>

#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"

using JSON = nlohmann::json;

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

inline JSON ReadJson(const char* path, const char* defaultJson)
{
    std::ifstream f(path);
    if (!f.is_open())
    {
        return JSON::parse(defaultJson);
    }

    JSON j = JSON::parse(f, nullptr, false);
    f.close();

    return j;
}

inline void SaveJson(const JSON& j, const char* path)
{
    std::string temp{path};
    temp += ".temp";
    std::ofstream f(temp);
    if (!f.is_open())
    {
        return;
    }

    f << j.dump(4);
    f.close();

    std::filesystem::rename(temp, path);
}

#endif //SHEEP_GOES_DEVILE_UTILITY_H
