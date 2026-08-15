//
// Created by Kamil on 15.08.2026.
//

#ifndef SHEEP_GOES_DEVILE_RANDOM_HPP
#define SHEEP_GOES_DEVILE_RANDOM_HPP
#include <random>

struct Random
{
    Random()
    {
        std::random_device rd;

        std::seed_seq seq{
            rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(),
            rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd()
        };

        Generator.seed(seq);;

        IntDistribution = std::uniform_int_distribution{ };
        FloatDistribution = std::uniform_real_distribution<float>{ };
        UIntDistribution = std::uniform_int_distribution<size_t>{ };
    }

    size_t GetUInt(const size_t min = 0, const size_t max = std::numeric_limits<size_t>::max())
    {
        return UIntDistribution(Generator, std::uniform_int_distribution<size_t>::param_type{min, max});
    }

    int GetInt(const int min = std::numeric_limits<int>::min(), const int max = std::numeric_limits<int>::max())
    {
        return IntDistribution(Generator, std::uniform_int_distribution<>::param_type{min, max});
    }

    float GetFloat(const float min = 0.0f, const float max = 1.0f)
    {
        return FloatDistribution(Generator, std::uniform_real_distribution<float>::param_type{min, max});
    }

    float GetValue()
    {
        return FloatDistribution(Generator, std::uniform_real_distribution<float>::param_type{0.0f, 1.0f});
    }
private:
    std::mt19937 Generator;
    std::uniform_int_distribution<int> IntDistribution;
    std::uniform_int_distribution<size_t> UIntDistribution;
    std::uniform_real_distribution<float> FloatDistribution;
};
#endif //SHEEP_GOES_DEVILE_RANDOM_HPP
