#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include <SDL2/SDL.h>

namespace AEOIAF_Utilities
{
    class Timer
    {
        public:
            Timer();

            uint32_t const GetStartTicks() { return startTicks; }
            uint32_t const GetPausedTicks() { return pausedTicks; }
            bool const GetIsPaused() { return bIsPaused; }
            bool const GetIsStarted() { return bIsStarted; }

            void Start();
            void Stop();
            void Pause();
            void Unpause();
            uint32_t GetTicks();

        private:
            uint32_t startTicks; //!< Member variable "startTicks"
            uint32_t pausedTicks; //!< Member variable "pausedTicks"
            bool bIsPaused; //!< Member variable "bIsPaused"
            bool bIsStarted; //!< Member variable "bIsStarted"
    };
}

#endif // TIMER_H
