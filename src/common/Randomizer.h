//
// Created by lejonmcgowan on 2/10/16.
//

#ifndef SAA_APPLICATION_RANDOMIZER_H
#define SAA_APPLICATION_RANDOMIZER_H

#include <random>
#include <functional>

class Randomizer
{
private:
    float minRange, maxRange;
    int seed;
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution;
    std::function<float()> random;
public:
    Randomizer(float minRange, float maxRange, int seed = -1) :
            minRange(minRange),
            maxRange(maxRange),
            seed(seed)
    {
        distribution = std::uniform_real_distribution<float>(minRange, maxRange);
        //because seeds are uints
        if (seed > -1)
            generator = std::default_random_engine(seed);

        std::default_random_engine myGenerator = generator;
        random = std::bind(distribution, std::move(myGenerator));
    }

    /**
     * get a number in the defined range, centered at zero
     */
    float getRandom()
    {
        return random();
    }

    /**
     * get a number centered around @pivot, with ranges given
     */
    float getRandom(float pivot)
    {
        return pivot + random();
    }

    /*todo: implement this function in case w need more flexibility with
        custom range, generator, distribution*/
    static float gerRandomCustom();

};

#endif //SAA_APPLICATION_RANDOMIZER_H
