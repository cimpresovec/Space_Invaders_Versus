#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "Globals.h"
#include "Functions.h"
#include "Classes.h"
#include "Objects.h"


using namespace std;

//Initlizacija
Enemy::Enemy()
{

	x = NULL;
	y = NULL;

	i_myY = NULL;

	box.x = NULL;
	box.y = NULL;

	box.w = 50;
	box.h = 25;

	created = true;


	alive = false;

	b_moving = false;

	frame = NULL;
}

void Enemy::set_up( int X, int Y, SDL_Surface * TYPE )
{
	x = X;
	y = Y;

	box.x = x;
	box.y = y;

	box.w = 50;
	box.h = 25;

	created = true;

	alive = true;

	frame = 1;

	type = TYPE;

}

void Enemy::show()
{
	if ( alive == true )
	{
		apply_surface( x, y, type, screen, NULL);
	}
}

void Enemy::animate( int enemy )
{
	if ( enemy == 1 )
	{
		switch ( frame )
		{
		case 1: type = small_enemy1; frame++; break;
		case 2: type = small_enemy2; frame = 1; break;
		}
	}

	else if ( enemy == 2 )
	{
		switch ( frame )
		{
		case 1: type = medium_enemy1; frame++; break;
		case 2: type = medium_enemy2; frame = 1; break;
		}
	}
}

bool Enemy::check_bulet2()
{
	box.x = x;
	box.y = y;

	move();

	for ( int bul = 0; bul < 3; bul++ )
	{

	if ( player_2.player1_bulet[bul].alive == true && check_collision(box, player_2.player1_bulet[bul].box) && alive == true)
	{
		player_2.player1_bulet[bul].alive = false;
		alive = false;
		Mix_PlayChannel(-1, m_explode, 0 );
		return true;
		
	}
	}


	if ( player_2.player1_laser[0].alive == true && check_collision(box, player_2.player1_laser[0].box) && alive == true)
	{
		alive = false;
		Mix_PlayChannel(-1, m_explode, 0 );
		return true;	
	}


	if  ( o_player2_attacker.o_bulet[0].alive == true && check_collision(box, o_player2_attacker.o_bulet[0].box ) && alive == true)
	{

		if ( o_player2_attacker.o_bulet[0].b_laser == true )
		{
			alive = false;
			Mix_PlayChannel(-1, m_explode, 0 );
		}
		
			
	}

	return false;

}

bool Enemy::check_bulet()
{
	box.x = x;
	box.y = y;

	move();

	for ( int bul = 0; bul < 3; bul++ )
	{
	if ( player_1.player1_bulet[bul].alive == true && check_collision(box, player_1.player1_bulet[bul].box) && alive == true)
	{
		player_1.player1_bulet[bul].alive = false;
		alive = false;
		Mix_PlayChannel(-1, m_explode, 0 );
		return true;
		
	}
	}

	if ( player_1.player1_laser[0].alive == true && check_collision(box, player_1.player1_laser[0].box) && alive == true)
	{
		alive = false;
		Mix_PlayChannel(-1, m_explode, 0 );
		return true;	
	}

	

	for ( int b = 0; b < 5; b++ )
	{
		if ( blocks.o_Block[b].o_bulet[0].alive == true && check_collision(box, blocks.o_Block[b].o_bulet[0].box) && alive == true)
		{
			alive = false;
			blocks.o_Block[b].o_bulet[0].alive = false;
			Mix_PlayChannel(-1, m_explode, 0 );
			return true;
		}
	}

	if  ( o_player2_attacker.o_bulet[0].alive == true && check_collision(box, o_player2_attacker.o_bulet[0].box ) && alive == true)
	{

		if ( o_player2_attacker.o_bulet[0].b_laser == true )
		{
			alive = false;
			Mix_PlayChannel(-1, m_explode, 0 );
		}
		
			
	}

	return false;
}

void Enemy::make_me()
{
	alive = true;
	y = 0;
	b_moving = true;

}

void Enemy::move()
{
	if ( b_moving == true )
	{
		y += 1;

		if ( y >= i_myY )
		{
			b_moving = false;
		}
	}
}
