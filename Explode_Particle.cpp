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

Explode_Particle::Explode_Particle()
{
	i_x = 0;
	i_y = 0;
	box.w = 20;
	box.h = 20;
	i_xvel = 0;
	i_yvel = 0;
	i_player = 1;
	i_a = 1;
	i_speed = 200;
	i_frame = 0;
	b_alive = false;
};

void Explode_Particle::set_up()
{
	i_player = 2;
}

void Explode_Particle::create( int x, int y )
{
	i_x = (float)x;
	i_y = (float)y;

	//Hitrost naredi med -200 do 200
	i_xvel = (float)((rand() % 400) - 200);
	i_yvel = (float)((rand() % 400) - 200);

	i_frame = 0;

	if ( i_player == 1 )
	{
	player_1.b_blastagain = true;
	}

	else { player_2.b_blastagain = true; player_1.b_blastagain = true; }

	b_alive = true;
}

void Explode_Particle::move( int delta )
{
	if ( b_alive == true )
	{
		i_x += i_xvel * (delta / 1000.f);
		i_y += i_yvel * (delta / 1000.f);

		box.x = (int)i_x;
		box.y = (int)i_y;
	
		i_frame++;

		check_enemy();
	}
}

void Explode_Particle::check_enemy()
{
	for ( int n = 0; n < 8; n++ )
	{
		if ( check_collision( box, enemycontrol.smallEnemy[n].box ) && enemycontrol.smallEnemy[n].alive == true )
		{
			b_alive = false;
			enemycontrol.smallEnemy[n].alive = false;
			if ( i_player == 1 )
			{o_player1_score.add_score(500);} else { o_player2_score.add_score(500);}
			Mix_PlayChannel(-1, m_explode, 0 );
		}
	}

	for ( int n = 0; n < 16; n++ )
	{
		if ( check_collision(box, enemycontrol.bigEnemy[n].box ) && enemycontrol.bigEnemy[n].alive == true )
		{
			b_alive = false;
			enemycontrol.bigEnemy[n].alive = false;
			if ( i_player == 1 )
			{o_player1_score.add_score(100);} else { o_player2_score.add_score(100);}
			Mix_PlayChannel(-1, m_explode, 0 );
		}
		if ( check_collision(box, enemycontrol.mediumEnemy[n].box ) && enemycontrol.mediumEnemy[n].alive == true )
		{
			b_alive = false;
			enemycontrol.mediumEnemy[n].alive = false;
			if ( i_player == 1 )
			{o_player1_score.add_score(250);} else { o_player2_score.add_score(250);}
			Mix_PlayChannel(-1, m_explode, 0 );
		}
	}
}

bool Explode_Particle::alive()
{
	return b_alive;
}

void Explode_Particle::show()
{
	if ( b_alive == true )
	{
		if ( i_frame > 50 )
		{
			b_alive = false;
		}

		if ( i_a == 1 )
		{
		apply_surface( (int)i_x, (int)i_y, s_blast[2], screen, NULL );
		}

		else
		{
			apply_surface( (int)i_x, (int)i_y, s_nuke, screen, NULL );
		}

	}
}
