//
// Created by Kamil on 15.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_UUID_H
#define SHEEP_GOES_DEVILE_UUID_H
#include <random>
#include "JSON.h"

struct UUID
{
    uint64_t Value;

    operator uint64_t() const
    {
        return Value;
    }

    UUID() : Value(0)
    {
    }

    UUID(const uint64_t value) : Value(value)
    {
    }
};

inline void to_json(JSON& j, const UUID& id)
{
    j["value"] = id;
}

inline void from_json(const JSON& j, UUID& id)
{
    ReadJsonValue(id, j, "value", UUID());
}

template<>
struct std::hash<UUID>
{
    std::size_t operator()(const UUID& uuid) const noexcept
    {
        return std::hash<uint64_t>()(uuid.Value);
    }
};
#endif //SHEEP_GOES_DEVILE_UUID_H
