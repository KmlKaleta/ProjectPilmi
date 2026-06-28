//
// Created by Kamil on 09.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_JSON_HPP
#define SHEEP_GOES_DEVILE_JSON_HPP
#include <iostream>

#include "nlohmann/JSON.hpp"
#include "nlohmann/json_fwd.hpp"

using JSON = nlohmann::json;

JSON ReadJson(const char* path);

void SaveJson(const JSON& j, const char* path);

template<typename T>
void ReadJsonValue(T& value, const JSON& j, const char* key, const T& defaultValue)
{
    value = defaultValue;
    const auto it = j.find(key);

    if (it == j.end())
        return;

    try
    {
        value = it->get<T>();
    } catch (const std::exception& e)
    {
        std::cerr << "[JSON] Invalid value for key: " << key
                << " (" << e.what() << ")\n";
    }
}

template<typename T>
void ReadJsonValue(T& value, const JSON& j, const T& defaultValue)
{
    value = defaultValue;
    try
    {
        value = j.get<T>();
    } catch (const std::exception& e)
    {
        std::cerr << "[JSON] Invalid value for key: " << " (" << e.what() << ")\n";
    }
}

#endif //SHEEP_GOES_DEVILE_JSON_HPP
