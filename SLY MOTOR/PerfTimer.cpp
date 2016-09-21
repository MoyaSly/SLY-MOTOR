#include "PerfTimer.h"
#include "SDL\include\SDL_timer.h"

int PerfTimer::freq = 0;

// ---------------------------------------------
PerfTimer::PerfTimer()
{
	if (freq == 0)
		freq = SDL_GetPerformanceFrequency();

	Start();
}

// ---------------------------------------------
void PerfTimer::Start()
{
	started_at = SDL_GetPerformanceCounter();
}

// ---------------------------------------------
double PerfTimer::ReadMs() const
{
	return 1000.0 * (double(SDL_GetPerformanceCounter() - started_at) / double(freq));
}

// ---------------------------------------------
int PerfTimer::ReadTicks() const
{
	return SDL_GetPerformanceCounter() - started_at;
}