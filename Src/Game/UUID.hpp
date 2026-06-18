//
// Created by Kamil on 15.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_UUID_H
#define SHEEP_GOES_DEVILE_UUID_H
#include <cstdint>
#include <random>

struct UUID
{
    uint64_t Value;

    operator uint64_t() const
    {
        return Value;
    }

    UUID(const uint64_t value) : Value(value)
    {
    }
};

template<>
struct std::hash<UUID>
{
    std::size_t operator()(const UUID& uuid) const noexcept
    {
        return std::hash<uint64_t>()(uuid.Value);
    }
};

struct UUIDFactory
{
    UUIDFactory()
    {
        Generator = std::mt19937_64(Random());
    }

    UUID Get()
    {
        return Distribution(Generator);
    }

private:
    std::random_device Random;
    std::mt19937_64 Generator;
    std::uniform_int_distribution<uint64_t> Distribution;
};

#endif //SHEEP_GOES_DEVILE_UUID_H
