#include "Timer.h"

using namespace AEOIAF_Utilities;

Timer::Timer()
{
    startTicks = 0;
    pausedTicks = 0;

    bIsStarted = false;
    bIsPaused = false;
}

void Timer::Start()
{
    bIsStarted = true;
    bIsPaused = false;
    
	startTicks = SDL_GetTicks();
    pausedTicks = 0;
}

void Timer::Stop()
{
    bIsStarted = false;
    bIsPaused = false;

    startTicks = 0;
    pausedTicks = 0;
}

void Timer::Pause()
{
    if(bIsStarted && !bIsPaused)
    {
        bIsPaused = true;

        pausedTicks = SDL_GetTicks() - startTicks;
        startTicks = 0;
    }
}

void Timer::Unpause()
{
    if(bIsStarted && bIsPaused)
    {
        bIsPaused = false;

        startTicks = SDL_GetTicks() - pausedTicks;
        pausedTicks = 0;
    }
}

uint32_t Timer::GetTicks()
{
    uint32_t time;

    if(bIsStarted)
    {
        if(bIsPaused)
            time = pausedTicks;
        else
            time = SDL_GetTicks() - startTicks;
    }

	else
		time = 0;

    return time;
}
