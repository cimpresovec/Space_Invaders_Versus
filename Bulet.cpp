#include <string>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "Objects.h"
#include "Globals.h"
#include "Functions.h"
#include "Classes.h"

using namespace std;

//Initili
Bulet::Bulet()
{
	x = 0;
	box.x = 0;
	y = 0;
	box.y = 0;
	
	box.w = 11;
	box.h = 25;

	yVel = 0;

	alive = false;

	b_laser = false;

	frame = 0;

	bulet_surface = bulet_frame0;
}

void Bulet::create(int X, int Y)
{
	x = (float)X;
	box.x = (int)x;
	y = (float)Y;
	box.y = (int)y;
	box.w = 20;
	yVel = (float)BULET_SPEED;
	alive = true;
	frame = 0;
}

void Bulet::show()
{
	if ( alive == true )
	{
		animate();
		apply_surface( (int)x, (int)y, bulet_surface, screen, NULL );
	}
}

void Bulet::animate()
{
	switch (frame)
	{
	case 0: bulet_surface = bulet_frame1; frame = 1; break;
	case 1: bulet_surface = bulet_frame0; frame = 0; break;
	}
}

void Bulet::move( Uint32 delta )
{
	if ( alive == true )
	{
		y += yVel * ( delta / 1000.f );

		box.x = (int)x + 7;
		box.y = (int)y;
	}

	if ( box.y + box.h < 0 )
	{
		alive = false;
	}

	if ( box.y > SCREEN_HEIGHT )
	{
		alive = false;
	}
}


