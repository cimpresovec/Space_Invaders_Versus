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

Buy_System_Attacker::Buy_System_Attacker()
{
	i_state = 0;
	i_x = 708;
	i_y = 15;

	b_buy = false;
	b_move = false;
}

void Buy_System_Attacker::handle_input()
{
	if ( event.type == SDL_KEYDOWN )
	{
		switch ( event.key.keysym.sym )
		{
		case SDLK_w: i_state -= 1; b_move = true; break;
		case SDLK_s: i_state += 1; b_move = true; break;
		case SDLK_g: b_buy = true; break;
		}
	}
}

void Buy_System_Attacker::move()
{

	if ( b_move == true )
	{
		if ( i_state < 0 ) { i_state = 6; } else if ( i_state > 6 ) { i_state = 0; }

		switch ( i_state )
		{
		case 0: i_y = 15; break;
		case 1: i_y = 55; break;
		case 2: i_y = 105; break;
		case 3: i_y = 155; break;
		case 4: i_y = 205; break;
		case 5: i_y = 255; break;
		case 6: i_y = 305; break;
		/*case 7: i_y = 355; break;
		case 8: i_y = 405; break;*/
		}
	}
}

void Buy_System_Attacker::buy()
{
	if ( b_buy == true )
	{
		if ( i_state == 0 )
		{
			if ( o_player2_score.get_score() >= 1000 )
			{
				enemycontrol.make_new();
				o_player2_score.change_score(-1000);
			}
		}

		if ( i_state == 1 )
		{
			if ( o_player2_score.get_score() >= 2000 )
			{
				enemycontrol.acceleration += 10;
				o_player2_score.change_score(-2000);
			}
		}

		if ( i_state == 2 )
		{
			if ( o_player2_score.get_score() >= 2000 )
			{
				if ( !(CHANCE <= 15) )
				{
					CHANCE -= 20;
					o_player2_score.change_score(-2000);

					if ( CHANCE <= 15 )
					{
						CHANCE = 15;
					}
				}

			}
		}

		if ( i_state == 3 )
		{
			if ( o_player2_score.get_score() >= 3000)
			{
				if ( player_1.b_fast == false )
				{
					player_1.b_fast = true;
					o_player2_attacker.add_time(400);
					o_player2_score.change_score(-3000);
				}
			}
		}

		if (  i_state == 4 )
		{
			if ( o_player2_score.get_score() >= 6500 )
			{
				if ( enemycontrol.b_ammo == false )
				{
					enemycontrol.b_ammo = true;
					o_player2_score.change_score(-6500);
				}}
		}


		if ( i_state == 5 )
		{
			if ( o_player2_score.get_score() >= 5000 )
			{
				if ( o_player2_attacker.get_laser() == false )
				{
					o_player2_attacker.laser();
					o_player2_score.change_score(-5000);
				}
			}
		}

		if ( i_state == 6 )
		{
			enemycontrol.sacrifice();
		}
					
		b_buy = false;
	}
}


void Buy_System_Attacker::show()
{
	apply_surface( i_x, i_y, s_select2, screen, NULL );
	apply_surface(710, 13, s_p2power[0], screen, NULL );
	apply_surface(710, 55 , s_p2power[1], screen, NULL);
	apply_surface(710, 105, s_p2power[2], screen, NULL);
	apply_surface(710, 155, s_p2power[3], screen, NULL);
	apply_surface(710, 205, s_p2power[4], screen, NULL);
	apply_surface(710, 255, s_p2power[5], screen, NULL);
	apply_surface(710, 305, s_p2power[6], screen, NULL);

}