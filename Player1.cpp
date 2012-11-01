#include <string>
#include <sstream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "Globals.h"
#include "Functions.h"
#include "Classes.h"
#include "Objects.h"

using namespace std;

//Initli
Player1::Player1()
{
	box.x = 350;
	box.y = 480;
	box.w = 50;
	box.h = 25;

	x = 350;
	y = 480;

	i_buletn = 1;

	int i_blastammo = 0;
	int i_shottime = 0;
	b_blast = false;
	b_nuke = false;
	b_super = true;
	i_lives = 0;
	b_blastagain = true;
	i_player = 1;

	xVel = 0;
	yVel = 0;

	shoting = false;

	moving = false;

	
	//Zapolni vector
	for ( s = 0; s < 8; s++ )
	{
		player1_Shadow.push_back(Shadow( (int)x, (int)y, player1_shadow));
	}

	for ( int bul = 0; bul < 3; bul++ )
	{
		player1_bulet.push_back(Bulet());
	}

	player1_laser.push_back(Bulet());

	o_blast.push_back(Bomb(8));

	o_nuke = new Bomb(25);


	s = 0;
}

void Player1::set_up()
{
	i_player = 2;
	x = 430;
	box.x = 430;
	o_blast[0].i_player = 2;
	o_nuke->i_player = 2;

}

//Handle inpit

void Player1::hande_input()
{
	if ( i_player == 2 )
	{
		if ( event.type == SDL_KEYDOWN )
	{
		switch ( event.key.keysym.sym )
		{
		case SDLK_a: xVel -= PLAYER_SPEED; break;
		case SDLK_d: xVel += PLAYER_SPEED; break;
		case SDLK_f: shoting = true; break;
		}
	}

	if ( event.type == SDL_KEYUP )
	{
		switch ( event.key.keysym.sym )
		{
		case SDLK_a: xVel += PLAYER_SPEED; break;
		case SDLK_d: xVel -= PLAYER_SPEED; break;
		case SDLK_f: shoting = false; break;
		}
	}	
	}

	else if ( i_player == 1 )
	{

	if ( event.type == SDL_KEYDOWN )
	{
		switch ( event.key.keysym.sym )
		{
		case SDLK_LEFT: xVel -= PLAYER_SPEED; break;
		case SDLK_RIGHT: xVel += PLAYER_SPEED; break;
		case SDLK_m: shoting = true; break;
		}
	}

	if ( event.type == SDL_KEYUP )
	{
		switch ( event.key.keysym.sym )
		{
		case SDLK_LEFT: xVel += PLAYER_SPEED; break;
		case SDLK_RIGHT: xVel -= PLAYER_SPEED; break;
		case SDLK_m: shoting = false; break;
		}
	}	
	}

}

void Player1::check_time()
{
	if ( i_shottime > 0 )
	{
		i_shottime -= (int)(60*(delta.get_ticks() / 1000.f));
		stringstream time;
		time << i_shottime;
		if ( i_player == 1 )
		{
			s_player1_time = TTF_RenderText_Solid(f_stats, time.str().c_str(), col_red);}
		else { s_player2_time = TTF_RenderText_Solid(f_stats, time.str().c_str(), col_green); }
	}
	else if ( i_shottime == 0 )
	{
		i_buletn = 1;
	}

}

void Player1::set_time(int time)
{
	i_shottime = time;
}

void Player1::blast()
{
	if ( i_player == 1 )
	{
		if ( event.type == SDL_KEYDOWN )
		{
			if ( event.key.keysym.sym == SDLK_COMMA )
			{
				if ( o_blast[0].o_particle[0].alive() == false && b_blastagain == true ) {b_blast = true;}
				if ( o_nuke->alive() == true ) { o_nuke->b_explode = true; }

			}
		}
	}

	else
	{
		if ( event.type == SDL_KEYDOWN )
		{
			if ( event.key.keysym.sym == SDLK_g )
			{
				if ( o_blast[0].o_particle[0].alive() == false && b_blastagain == true ) {b_blast = true;}
				if ( o_nuke->alive() == true ) { o_nuke->b_explode = true; }

			}
		}
	}
	
}

//Premakni odvisno od FPS
void Player1::move(Uint32 delta)
{
	if ( b_fast == true )
	{
		x += (xVel * (delta / 1000.f)) / 2;
	}

	else
	{
	x += xVel * (delta / 1000.f);
	}

	if ( x < 100 || x + box.w > 700 )
	{
		x -= xVel * ( delta / 1000.f );
	}

	box.x = (int)x;

	for ( int bul = 0; bul < 3; bul++ )
	{
		player1_bulet[bul].move(delta);
	}

	player1_laser[0].move(delta);

	o_blast[0].move(delta);
	o_nuke->move(delta);
}

//Strelaje
void Player1::shot()
{
	if ( shoting == true && player1_bulet[0].alive == false && player1_bulet[1].alive == false && player1_bulet[2].alive == false && player1_laser[0].alive == false)
	{
		if ( i_buletn == 1 )
		{
			player1_bulet[0].create( (int)box.x + 16, (int)box.y - 25);
			shoting = false;
		}

		else if ( i_buletn == 2 )
		{
			player1_bulet[0].create( (int)box.x + 8, (int)box.y - 25);
			player1_bulet[1].create( (int)box.x + 20, (int)box.y - 25);
			shoting = false;
		}

		else if  ( i_buletn == 3 )
		{
			player1_bulet[0].create( (int)box.x + 8, (int)box.y - 25);
			player1_bulet[1].create( (int)box.x + 20, (int)box.y - 25);
			player1_bulet[2].create( (int)box.x + 14, (int)box.y - 30);
			shoting = false;
		}

		else if ( i_buletn == 4 )
		{
			player1_laser[0].create( (int)box.x + 16, (int)box.y - 25);
			shoting = false;
		}
	}

	if ( b_blast == true )
	{
		if ( i_blastammo > 0 )
		{
			if ( o_blast[0].alive() == false )
			{
				o_blast[0].create( (int)x + 16, (int)y - 10, -200 );
			
				i_blastammo--;
				b_blastagain = false;
			}
		}

		b_blast = false;
	}

	if ( b_nuke == true )
	{
		if ( o_nuke->alive() == false )
		{
			o_nuke->create( (int)x + 16, (int)y - 10, - 200 );
			o_nuke->i_a = 2;
		}

		b_nuke = false;
	}

}

void Player1::add_time(int time)
{
	i_shottime += time;
}

int Player1::get_lives()
{
	return i_lives;
}

void Player1::show_stats()
{
	if ( i_lives <= 0 )
	{

	if ( GAME_STATE == VERSUS )
		{
			STATE_SET = WIN_SCREEN;	
		}

		else if ( GAME_STATE == GAME )
		{
			STATE_SET = GAME_OVER;
	}

		else if ( GAME_STATE == GAME_2_PLAY )
		{
			STATE_SET = LOSE_TWO;
		}
	}

	stringstream bombs;

	bombs << "B: " << i_blastammo;

	if ( i_player == 1 )
	{ 
		s_player1_bombs = TTF_RenderText_Solid(f_stats, bombs.str().c_str(), col_red);
		switch ( i_buletn )
		{
		case 1: s_player1_shot = TTF_RenderText_Solid(f_stats, "Single", col_red); break;
		case 2: s_player1_shot = TTF_RenderText_Solid(f_stats, "Double", col_red); break;
		case 3: s_player1_shot = TTF_RenderText_Solid(f_stats, "Triple", col_red); break;
		case 4: s_player1_shot = TTF_RenderText_Solid(f_stats, "Laser", col_red); break;
		}

		stringstream lives;

		lives << "Lives: " << i_lives;

		s_player1_lives = TTF_RenderText_Solid(f_stats, lives.str().c_str(), col_red);
		
		apply_surface(15, 520, s_player1_shot, screen, NULL);
		apply_surface( 15, 570, s_player1_bombs, screen, NULL );
		apply_surface(15, 545, s_player1_time, screen, NULL);
		apply_surface(110, 490, s_player1_lives, screen, NULL);
	}


	else if ( i_player == 2 )
	{ 
		s_player2_bombs = TTF_RenderText_Solid(f_stats, bombs.str().c_str(), col_green); 

		switch ( i_buletn )
		{
		case 1: s_player2_shot = TTF_RenderText_Solid(f_stats, "Single", col_green); break;
		case 2: s_player2_shot = TTF_RenderText_Solid(f_stats, "Double", col_green); break;
		case 3: s_player2_shot = TTF_RenderText_Solid(f_stats, "Triple", col_green); break;
		case 4: s_player2_shot = TTF_RenderText_Solid(f_stats, "Laser", col_green); break;
		}

		stringstream lives;

		lives << "Lives: " << i_lives;

		s_player2_lives = TTF_RenderText_Solid(f_stats, lives.str().c_str(), col_green);
		
		apply_surface(715, 520, s_player2_shot, screen, NULL);
		apply_surface(715, 570, s_player2_bombs, screen, NULL );
		apply_surface(715, 545, s_player2_time, screen, NULL);
		apply_surface(690 - s_player2_lives->w , 490, s_player2_lives, screen, NULL);
	}
}


void Player1::set_lives(int set)
{
	i_lives += set;
}

//Prikaz
void Player1::show()
{	
	show_shadow();
	for ( int bul = 0; bul < 3; bul++ )
	{
		player1_bulet[bul].show();
	}

	player1_laser[0].show();

	o_blast[0].show();
	o_nuke->show();
	show_stats();
	

	if ( i_player == 1 )
	{
		apply_surface( (int)x, (int)y, player1, screen, NULL );
	}

	else if ( i_player == 2 )
	{
		apply_surface( (int)x, (int)y, player2, screen, NULL );
	}
}

void Player1::show_shadow()
{ 
	//Senca delo
	//Èe je senca dosta dugo gor
	if ( player1_Shadow[s].dead() == true )
	{
		player1_Shadow[s].alive = false;
	}

	//Naredi novo senco
	player1_Shadow[s].set_up( (int)x, (int)y, player1_shadow );

	//Nariši sence
	for ( se = 0; se < 8; se++ )
	{
		player1_Shadow[se].show();
	}

	//Poveèej številko sence
	s++;

	if ( s >= 8 )
	{
		s = 0;
	}
}

void Player1::clean_up()
{
	player1_laser[0].alive = false;
	for ( int n = 0; n < 3; n++ )
	{
		player1_bulet[n].alive = false;
	}

	b_nuke = false;
	o_nuke->b_alive = false;


	o_nuke->b_alive = false;
	o_blast[0].b_alive = false;
	i_blastammo = 0;
	i_lives = 0;
	i_shottime = 0;
	o_player1_score.change_score(0);

	for ( int n = 0; n < 25; n++ )
	{
		o_nuke->o_particle[n].b_alive = false;
	}

	for ( int o = 0; o < 8; o++)
	{
		o_blast[0].o_particle[o].b_alive = false;
	}

	i_buletn = 1;
}

