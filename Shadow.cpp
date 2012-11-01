#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "Globals.h"
#include "Objects.h"
#include "Functions.h"
#include "Classes.h"

using namespace std;

//Initili
Shadow::Shadow( int X, int Y, SDL_Surface * TYPE)
{
	x = X;
	y = Y;

	alive = true;

	frame = 0;

	type = TYPE;
}

void Shadow::set_up(int X, int Y, SDL_Surface* TYPE)
{
	x = X;
	y = Y;

	frame = 0;

	alive = true;

	type = TYPE;
}

void Shadow::show()
{
	apply_surface(x, y, type, screen, NULL);
	frame += (int)(60*(delta.get_ticks() / 1000.f));
}

bool Shadow::dead()
{
	if ( frame >= 600 )
	{
		return true;
	}

	return false;
}