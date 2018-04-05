#include "Random.h"

using namespace AEOIAF_Utilities;

Random::Random()
{
    seed = time(NULL);
    x = seed;
}

Random::Random(uint64_t newSeed)
{
    seed = newSeed;
    x = newSeed;
}

uint64_t Random::GetRandomNumber()
{
    //I am unsure the significance of these numbers, they seem arbitrarily chosen
    //Anyways, we basically XOR x after shifting x by these before multiplying it
    //by a gargantuan number
    const uint64_t A = 21;
    const uint64_t B = 35;
    const uint64_t C = 4;

    x ^= x >> A;
    x ^= x << B;
    x ^= x >> C;

    //Like the constants above, I am unsure of the significance of this particular
    //number
    return x * (uint64_t)(2685821657736338717);
}

int Random::GetRandomNumber(int minVal, int maxVal)
{
    uint64_t randVal = GetRandomNumber();

    return (randVal % maxVal) + minVal;
}

float Random::GetRandomFloat()
{
    //Use this for modding randVal, and also dividing by this.
    //The greater this number, the more randomness in our floats.
    //The extra 1 allows us to potentially have 1.0f returned
    const int MAX_SIZE = 10001;

    uint64_t randVal = GetRandomNumber();
    randVal = (randVal % MAX_SIZE); //Pretend we are putting this in the range of 0 to MAX_SIZE

    return (float)randVal / (float)MAX_SIZE;
}
