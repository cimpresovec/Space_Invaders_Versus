#include <string>
#include <sstream>
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

Attacker::Attacker()
{
	i_x = 350;
	i_y = 0;

	i_xVel = 0;
	i_speed = 100;
	box.x = 350;
	box.y = 0;
	box.w = 100;
	i_time = 0;
	box.h = 25;
	b_shot = false;
	b_laser = false;

	o_bulet.push_back(Bulet());
}

void Attacker::handle_input()
{
	if ( event.type == SDL_KEYDOWN )
	{
		switch ( event.key.keysym.sym )
		{
		case SDLK_a: i_xVel -= i_speed; break;
		case SDLK_d: i_xVel += i_speed; break;
		case SDLK_f: b_shot = true; break;
		}
	}

	if ( event.type == SDL_KEYUP )
	{
		switch ( event.key.keysym.sym )
		{
		case SDLK_a: i_xVel += i_speed; break;
		case SDLK_d: i_xVel -= i_speed; break;
		case SDLK_f: b_shot = false; break;
		}
	}
}

void Attacker::move(Uint32 delta)
{
	i_x += i_xVel * ( delta / 1000.f );

	if ( i_x < 100 || i_x + box.w > 700 )
	{
		i_x -= i_xVel * (delta / 1000.f );
	}

	o_bulet[0].move(delta);
	if ( i_time > 0 )
	{
		i_time -= (int)(60*(delta / 1000.f));

	}

	if ( i_time <= 0 )
	{
		i_time = 0;
		player_1.b_fast = false;
	}

}

void Attacker::check_player()
{
	if ( o_bulet[0].alive == true && check_collision(o_bulet[0].box, player_1.box) == true ) 
	{
		if ( o_bulet[0].b_laser == true )
		{

			player_1.set_lives(-1);
			o_player2_score.add_score(500);
		}

		else
		{
			o_bulet[0].alive = false;
			player_1.set_lives(-1);
			o_player2_score.add_score(500);
		}
	}
}

void Attacker::laser()
{
	if ( b_laser == false ) { b_laser = true; }
	else { b_laser = false; }
}

void Attacker::add_time(int x)
{
	i_time += x;
}

void Attacker::show()
{
	apply_surface ( (int)i_x, (int)i_y, s_attacker, screen, NULL );
	o_bulet[0].show();
	show_stats();
}

void Attacker::show_stats()
{
	stringstream acc;

	acc << "Acc:" << enemycontrol.acceleration;

	s_player2_acc = TTF_RenderText_Solid(f_stats, acc.str().c_str(), col_black);

	stringstream cnc;

	cnc << "1:" << CHANCE;

	s_player2_chance = TTF_RenderText_Solid(f_stats, cnc.str().c_str(), col_black); 

	stringstream time;

	time << i_time;

	s_player2_time = TTF_RenderText_Solid(f_stats, time.str().c_str(), col_black);

	apply_surface( 720, 520, s_player2_acc, screen, NULL );
	apply_surface( 720, 545, s_player2_chance, screen, NULL);
	apply_surface( 720, 570, s_player2_time, screen, NULL);

}

bool Attacker::get_laser()
{
	if ( b_laser == true )
	{
		return true;
	}
	else {
		return false;}
}

void Attacker::shot()
{
	check_player();

	if ( b_shot == true && o_bulet[0].alive == false )
	{
		if ( b_laser == false )
		{
		o_bulet[0].create( (int)i_x + 40, (int)i_y + 25 );
		o_bulet[0].yVel = 100;
		o_bulet[0].bulet_surface = s_attacker_shot;
		o_bulet[0].frame = 3;
		o_bulet[0].box.w = 25;
		o_bulet[0].b_laser = false;
		}

		else
		{
			o_bulet[0].create( (int)i_x, (int)i_y + 25 );
			o_bulet[0].yVel = 100;
			o_bulet[0].bulet_surface = s_biglaser;
			o_bulet[0].frame = 3;
			o_bulet[0].box.w = 100;
			o_bulet[0].b_laser = true;
			b_shot = false;
			b_laser = false;
		}
	}


}
