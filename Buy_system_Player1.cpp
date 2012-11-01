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

Buy_Sys_Play1::Buy_Sys_Play1()
{
	i_state = 0;
	i_y = 15;
	i_x = 8;
	i_player = 1;
	b_move = false;
	b_buy = false;
	for ( int n = 0; n < 8; n++ )
	{
		b_unlocked[n] = false;
	}
}

void Buy_Sys_Play1::set_up()
{
	i_player = 2;
	i_y = 15;
	i_x = 708;
}

void Buy_Sys_Play1::reset()
{
	for ( int n = 0; n < 8; n++ )
	{
		b_unlocked[n] = false;
	}

	for ( int n = 0; n < 9; n++ )
	{
		stringstream m;
		m << "data/gfx/p1_locked" << n << ".png";
		if ( i_player == 1 )
		{
			s_p1power[n] = load_image(m.str());
		}
		else if ( i_player == 2 )
		{
			s_p3power[n] = load_image(m.str());
		}
	}
}


void Buy_Sys_Play1::handle_input()
{
	if ( i_player == 1 )
	{
	if ( event.type == SDL_KEYDOWN )
	{
		switch ( event.key.keysym.sym )
		{
		case SDLK_UP: i_state -= 1; b_move = true; break;
		case SDLK_DOWN: i_state += 1; b_move = true; break;
		case SDLK_PERIOD: b_buy = true; break;
		}
	}
	}

	else
	{
		if ( event.type == SDL_KEYDOWN )
		{
			switch ( event.key.keysym.sym )
			{
			case SDLK_w: i_state -= 1; b_move = true; break;
			case SDLK_s: i_state += 1; b_move = true; break;
			case SDLK_h: b_buy = true; break;
			}
		}
	}
}

void Buy_Sys_Play1::move()
{
	if ( b_move == true )
	{
		if ( i_state < 0 ) { if ( GAME_STATE != VERSUS ) {i_state = 7;} else { i_state = 6;} }
		else
		{
			if ( GAME_STATE != VERSUS )
			{
				if ( i_state > 7 ) { i_state = 0;}
			}

			else { if ( i_state > 6 ) { i_state = 0;}}
		}
			



		switch ( i_state )
		{
		case 0: i_y = 15; break;
		case 1: i_y = 55; break;
		case 2: i_y = 105; break;
		case 3: i_y = 155; break;
		case 4: i_y = 205; break;
		case 5: i_y = 255; break;
		case 6: i_y = 305; break;
		case 7: i_y = 355; break;
		case 8: i_y = 405; break;
		}
	}
}

void Buy_Sys_Play1::buy2()
{	
	if ( b_buy == true )
	{
		if ( i_state == 0)
		{
			if ( o_player2_score.get_score() >= 3000 && b_unlocked[0] == true )
			{
				for( int num = 0; num < 2; num ++ )
				{
					for( int b = 0; b < 5; b++ )
					{
						blocks.o_Block[b].heal();
					}
				}

				o_player2_score.change_score(-3000);		
			}

			else if ( o_player2_score.get_score() >= 1000 && b_unlocked[0] == false )
			{
				b_unlocked[0] = true;
				o_player2_score.change_score(-1000);
				s_p3power[0] = load_image("data/gfx/p1_power0.png");
			}
		}
		
		else if ( i_state == 1 )
			{
				if ( o_player2_score.get_score() >= 4000 && b_unlocked[1] == true )
				{
					player_2.i_buletn = 2; 

					o_player2_score.change_score(-4000);
					player_2.set_time(600);

				}

				else if ( o_player2_score.get_score() >= 5000 && b_unlocked[1] == false )
				{
					b_unlocked[1] = true;
					o_player2_score.change_score(-5000);
					s_p3power[1] = load_image("data/gfx/p1_power1.png");
				}
			}

		else if ( i_state == 2 )
			{
				if ( o_player2_score.get_score() >= 6500 && b_unlocked[2] == true )
				{
					player_2.i_buletn = 3; 

					o_player2_score.change_score(-6500);
					player_2.set_time(450);

				}

				else if ( o_player2_score.get_score() >= 7500 && b_unlocked[2] == false )
				{
					b_unlocked[2] = true;
					o_player2_score.change_score(-7500);
					s_p3power[2] = load_image("data/gfx/p1_power2.png");
				}
			}

		else if ( i_state == 3 )
			{
				if ( o_player2_score.get_score() >= 5000 && b_unlocked[3] == true )
				{
					player_2.i_blastammo++;

					o_player2_score.change_score(-5000);
				}

				else if ( o_player2_score.get_score() >= 6000 && b_unlocked[3] == false )
				{
					b_unlocked[3] = true;
					o_player2_score.change_score(-6000);
					s_p3power[3] = load_image("data/gfx/p1_power3.png");
				}
			}

		else if ( i_state == 4 )
			{
				if ( o_player2_score.get_score() >= 7500 && b_unlocked[4] == true )
				{
					player_2.i_buletn = 4;
					player_2.set_time(100);
					o_player2_score.change_score(-7500);
				}

				else if ( o_player2_score.get_score() >= 8500 && b_unlocked[4] == false )
				{
					b_unlocked[4] = true;
					o_player2_score.change_score(-8500);
					s_p3power[4] = load_image("data/gfx/p1_power4.png");
				}

			}

		else if ( i_state == 5 )
		{
			if ( o_player2_score.get_score() >= 2000 && b_unlocked[5] == true )
			{
				player_2.add_time(200);
				o_player2_score.change_score(-2000);
			}

			else if ( o_player2_score.get_score() >= 3500 && b_unlocked[5] == false )
				{
					b_unlocked[5] = true;
					o_player2_score.change_score(-3500);
					s_p3power[5] = load_image("data/gfx/p1_power5.png");
				}
		}

		else if ( i_state == 6 )
		{
			if ( o_player2_score.get_score() >= 6000 && b_unlocked[6] == true)
			{
				blocks.b_shot = true;
				o_player2_score.change_score(-6000);
			}

			else if ( o_player2_score.get_score() >= 7000 && b_unlocked[6] == false )
				{
					b_unlocked[6] = true;
					o_player2_score.change_score(-7000);
					s_p3power[6] = load_image("data/gfx/p1_power6.png");
				}
		}

		else if ( i_state == 7 )
		{
			if ( o_player2_score.get_score() >= 15000 && b_unlocked[7] == true && player_2.o_nuke->alive() == false && player_2.b_super == true)
			{
				player_2.b_nuke = true;
				player_2.b_super = false;
				o_player2_score.change_score(-15000);
			}

			else if ( o_player2_score.get_score() >= 18000 && b_unlocked[7] == false )
				{
					b_unlocked[7] = true;
					o_player2_score.change_score(-18000);
					s_p3power[7] = load_image("data/gfx/p1_power7.png");
				}
		}

			
		b_buy = false;
	}
}

void Buy_Sys_Play1::buy()
{	
	if ( b_buy == true )
	{
		if ( i_state == 0)
		{
			if ( o_player1_score.get_score() >= 3000 && b_unlocked[0] == true )
			{
				for( int num = 0; num < 2; num ++ )
				{
					for( int b = 0; b < 5; b++ )
					{
						blocks.o_Block[b].heal();
					}
				}

				o_player1_score.change_score(-3000);		
			}

			else if ( o_player1_score.get_score() >= 1000 && b_unlocked[0] == false )
			{
				b_unlocked[0] = true;
				o_player1_score.change_score(-1000);
				s_p1power[0] = load_image("data/gfx/p1_power0.png");
			}
		}
		
		else if ( i_state == 1 )
			{
				if ( o_player1_score.get_score() >= 4000 && b_unlocked[1] == true )
				{
					player_1.i_buletn = 2; 

					o_player1_score.change_score(-4000);
					player_1.set_time(600);

				}

				else if ( o_player1_score.get_score() >= 5000 && b_unlocked[1] == false )
				{
					b_unlocked[1] = true;
					o_player1_score.change_score(-5000);
					s_p1power[1] = load_image("data/gfx/p1_power1.png");
				}
			}

		else if ( i_state == 2 )
			{
				if ( o_player1_score.get_score() >= 6500 && b_unlocked[2] == true )
				{
					player_1.i_buletn = 3; 

					o_player1_score.change_score(-6500);
					player_1.set_time(450);

				}

				else if ( o_player1_score.get_score() >= 7500 && b_unlocked[2] == false )
				{
					b_unlocked[2] = true;
					o_player1_score.change_score(-7500);
					s_p1power[2] = load_image("data/gfx/p1_power2.png");
				}
			}

		else if ( i_state == 3 )
			{
				if ( o_player1_score.get_score() >= 5000 && b_unlocked[3] == true )
				{
					player_1.i_blastammo++;

					o_player1_score.change_score(-5000);
				}

				else if ( o_player1_score.get_score() >= 6000 && b_unlocked[3] == false )
				{
					b_unlocked[3] = true;
					o_player1_score.change_score(-6000);
					s_p1power[3] = load_image("data/gfx/p1_power3.png");
				}
			}

		else if ( i_state == 4 )
			{
				if ( o_player1_score.get_score() >= 7500 && b_unlocked[4] == true )
				{
					player_1.i_buletn = 4;
					player_1.set_time(100);
					o_player1_score.change_score(-7500);
				}

				else if ( o_player1_score.get_score() >= 8500 && b_unlocked[4] == false )
				{
					b_unlocked[4] = true;
					o_player1_score.change_score(-8500);
					s_p1power[4] = load_image("data/gfx/p1_power4.png");
				}

			}

		else if ( i_state == 5 )
		{
			if ( o_player1_score.get_score() >= 2000 && b_unlocked[5] == true )
			{
				player_1.add_time(200);
				o_player1_score.change_score(-2000);
			}

			else if ( o_player1_score.get_score() >= 3500 && b_unlocked[5] == false )
				{
					b_unlocked[5] = true;
					o_player1_score.change_score(-3500);
					s_p1power[5] = load_image("data/gfx/p1_power5.png");
				}
		}

		else if ( i_state == 6 )
		{
			if ( o_player1_score.get_score() >= 6000 && b_unlocked[6] == true)
			{
				blocks.b_shot = true;
				o_player1_score.change_score(-6000);
			}

			else if ( o_player1_score.get_score() >= 7000 && b_unlocked[6] == false )
				{
					b_unlocked[6] = true;
					o_player1_score.change_score(-7000);
					s_p1power[6] = load_image("data/gfx/p1_power6.png");
				}
		}

		else if ( i_state == 7 )
		{
			if ( o_player1_score.get_score() >= 15000 && b_unlocked[7] == true && player_1.o_nuke->alive() == false && player_1.b_super == true)
			{
				player_1.b_nuke = true;
				player_1.b_super = false;
				o_player1_score.change_score(-15000);
			}

			else if ( o_player1_score.get_score() >= 18000 && b_unlocked[7] == false )
				{
					b_unlocked[7] = true;
					o_player1_score.change_score(-18000);
					s_p1power[7] = load_image("data/gfx/p1_power7.png");
				}
		}

			
		b_buy = false;
	}
}

void Buy_Sys_Play1::unlock()
{
	for ( int u = 0; u < 8; u++ )
	{
		b_unlocked[u] = true;
	}

	if ( i_player == 1 )
	{
	for ( int n = 0; n < 8; n++ )
	{
		stringstream m;
		m << "data/gfx/p1_power" << n << ".png";
		s_p1power[n] = load_image(m.str());
	}
	}

	else 
	{
		for ( int n = 0; n < 8; n++ )
		{
			stringstream m;
			m << "data/gfx/p1_power" << n << ".png";
			s_p1power[n] = load_image(m.str());
		}
	}
}

void Buy_Sys_Play1::show()
{
	if ( i_player == 1 )
	{
	apply_surface( i_x, i_y, s_select1, screen, NULL );
	apply_surface(10, 13, s_p1power[0], screen, NULL );
	apply_surface(10, 55 , s_p1power[1], screen, NULL);
	apply_surface(10, 105, s_p1power[2], screen, NULL);
	apply_surface(10, 155, s_p1power[3], screen, NULL);
	apply_surface(10, 205, s_p1power[4], screen, NULL);
	apply_surface(10, 255, s_p1power[5], screen, NULL);
	apply_surface(10, 305, s_p1power[6], screen, NULL);

	if ( GAME_STATE != VERSUS )
	{
	apply_surface(10, 355, s_p1power[7], screen, NULL);
	}
	}

	else if ( i_player == 2 )
	{
		apply_surface( i_x, i_y, s_select1, screen, NULL );

		if ( b_unlocked[0] == false )
		{
			apply_surface(710,13,s_locked,screen,NULL);
		}
		else
		{
		apply_surface(710, 13 , s_p3power[0], screen, NULL );
		}
		apply_surface(710, 55 , s_p3power[1], screen, NULL);
		apply_surface(710, 105, s_p3power[2], screen, NULL);
		apply_surface(710, 155, s_p3power[3], screen, NULL);
		apply_surface(710, 205, s_p3power[4], screen, NULL);
		apply_surface(710, 255, s_p3power[5], screen, NULL);
		apply_surface(710, 305, s_p3power[6], screen, NULL);
		apply_surface(710, 355, s_p3power[7], screen, NULL);
	}

	
}


		