/**
 * Copyright (c) 2016 Cal Poly Capstone Team Rocket
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in the
 * Software without restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */
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
