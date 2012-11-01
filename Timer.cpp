#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "Globals.h"
#include "Functions.h"
#include "Classes.h"

using namespace std;

//Initilizacija
Timer::Timer()
{
	ticks = 0;
}

void Timer::start()
{
	ticks = SDL_GetTicks();
}

int Timer::get_ticks()
{
	return SDL_GetTicks() - ticks;
}

void Timer::restart()
{
	ticks = SDL_GetTicks();
}
