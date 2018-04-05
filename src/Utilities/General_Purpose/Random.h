//Liam "AFishyFez" Wynn, 12/12/2014, AEOIAF

/*
The purpose of this file is to hold the definition and prototype
for the Random object for AEOIAF. The code used is a simple xorshift,
as seen here: http://en.wikipedia.org/wiki/Xorshift
I picked this because of its simplicity and fastness. In addition to
the algorithm proper, I've taken the liberty of adding a few extra
methods for extra versatility. I'd prefer to use a Random object system
a la C# because: 1. For learning purposes and 2. It offers what I believe
to be more flexibility because of the use of multiple random objects with different
seeds and whatnot.
*/

#ifndef AEOIAF_RAND
#define AEOIAF_RAND

#include <time.h>
#include <cstdint>

namespace AEOIAF_Utilities
{
    class Random
    {
        public:
            Random(); //Will initialize the seed based on time
            Random(uint64_t newSeed); //Will initialize based on a user given seed

            uint64_t GetSeed() const { return seed; }

            uint64_t GetRandomNumber(); //The actual xorshift process. Returns a number from 0 to the unsigned 64 bit integer maximum
            int GetRandomNumber(int minVal, int maxVal); //Returns an integer from minVal to maxVal
            float GetRandomFloat(); //Returns a float from 0.0 to 1.0

        private:
            uint64_t seed; //This simply holds onto the original seed from when the object was initialized
            uint64_t x; //This is used in GetRandomNumber. Beginning as seed, its value is modified as the object is used
    };
}

#endif // AEOIAF_RAND
