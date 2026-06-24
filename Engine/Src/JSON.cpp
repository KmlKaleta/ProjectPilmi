//
// Created by Kamil on 09.06.2026.
//
#include "JSON.h"
#include <fstream>

JSON ReadJson(const char* path)
{
    std::ifstream f(path);
    if (!f.is_open())
    {
        return JSON::object();
    }

    JSON j = JSON::parse(f, nullptr, false);
    f.close();

    if (j.is_discarded())
    {
        return JSON::object();
    }

    return j;
}

void SaveJson(const JSON& j, const char* path)
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