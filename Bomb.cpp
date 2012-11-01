#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "Objects.h"
#include "Globals.h"
#include "Functions.h"
#include "Classes.h"

using namespace std;

Bomb::Bomb( int part )
{
	i_x = 0;
	i_y = 0;

	box.w = 25;
	box.h = 25;

	i_yvel = 0;

	i_frame = 0;

	i_a = 1;

	i_player = 1;
	i_time = 0;

	i_particles = part;

	b_alive = false;
	b_explode = false;

	for ( int n = 0; n < i_particles; n++ )
	{
		o_particle.push_back(Explode_Particle());
	}
}

bool Bomb::alive()
{
	return b_alive;
}

void Bomb::button()
{
	if ( b_alive == true )
	{
		if ( i_player == 1 )
		{
		if ( event.type == SDL_KEYDOWN )
		{
			if ( event.key.keysym.sym == SDLK_COMMA )
			{
				b_explode = true;
			}
		}
		}

		else
		{
			if ( event.type == SDL_KEYDOWN )
			{
				if ( event.key.keysym.sym == SDLK_g )
				{
					b_explode = true;
				}
			}
		}

	}
}

void Bomb::create(int x, int y, int speed)
{
	i_x = x;
	i_y = (float)y;

	b_alive = true;

	i_yvel = (float)speed;

}

void Bomb::move(int delta)
{
	i_y += i_yvel * ( delta / 1000.f );

	i_time++;

	box.x = (int)i_x;
	box.y = (int)i_y;

	if ( i_time > 10 )
	{
		i_frame++;
		if ( i_frame >= 3 ) { i_frame = 0; }
		i_time = 0;
	}

	for ( int n = 0; n < i_particles; n++ )
	{
		o_particle[n].move(delta);
	}


	explode();

}

void Bomb::show()
{
	if ( i_a == 1 )
	{
	if ( b_alive == true ) {apply_surface( i_x, (int)i_y, s_blast[1], screen, NULL );}
	}

	if ( i_a == 2 )
	{
		if ( b_alive == true ) {apply_surface( i_x, (int)i_y, s_nuke, screen, NULL );}
	}

	for ( int n = 0; n < i_particles; n++ )
	{
		o_particle[n].show();
	}
}

void Bomb::explode()
{
	if ( b_alive == true && b_explode == true)
	{
		b_alive = false;
		b_explode = false;

		for ( int n = 0; n < i_particles; n++ )
		{
			o_particle[n].set_up();
			o_particle[n].create( (int)i_x, (int)i_y );
			if ( i_a == 2 )
			{
				o_particle[n].i_a = 2;
			}
		}
	}

}

