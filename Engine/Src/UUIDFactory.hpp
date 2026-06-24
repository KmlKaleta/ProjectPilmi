//
// Created by Kamil on 18.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_UUID_FACTORY_H
#define SHEEP_GOES_DEVILE_UUID_FACTORY_H
#include <random>
#include "UUID.hpp"

struct UUIDFactory
{
    UUIDFactory()
    {
        std::random_device rd;

        std::seed_seq seq{
            rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(),
            rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd()
        };

        Generator.seed(seq);;

        Distribution = std::uniform_int_distribution<uint64_t>{
            1, std::numeric_limits<uint64_t>::max()
        };
    }

    UUID Get()
    {
        return Distribution(Generator);
    }

private:
    std::mt19937_64 Generator;
    std::uniform_int_distribution<uint64_t> Distribution;
};

#endif //SHEEP_GOES_DEVILE_UUID_FACTORY_H
