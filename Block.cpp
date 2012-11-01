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

Block::Block()
{
	box.w = 50;
	box.x = 0;
	box.y = 0;
	box.h = 25;

	b_shot = false;
	state = 0;

	type = NULL;

	o_bulet = new Bulet();
}

void Block::create(int x, int y)
{
	box.x = x;
	box.y = y;

	alive = true;

	b_shot = false;

	state = 0;

	o_bulet[0].alive = false;

	type = s_block00;
}

void Block::allow_shot()
{
	b_shot = true;
}

void Block::shot()
{
	if ( b_shot == true ) 
	{
		o_bulet[0].create(box.x + 12, box.y - 16);
		o_bulet[0].bulet_surface = s_blockbulet;
		o_bulet[0].frame = 3;
		o_bulet[0].box.w = 25;
		b_shot = false;
	}

	b_shot = false;
}


void Block::check_bulet()
{
	for ( int bul = 0; bul < 3; bul++ )
	{
	if ( player_1.player1_bulet[bul].alive == true && check_collision(box, player_1.player1_bulet[bul].box) && alive == true )
		{
			player_1.player1_bulet[bul].alive = false;
			change_state();
			if ( GAME_STATE == VERSUS )
			{
				o_player2_score.add_score(100);
			}
		}

	if ( player_2.player1_bulet[bul].alive == true && check_collision(box, player_2.player1_bulet[bul].box) && alive == true )
		{
			player_2.player1_bulet[bul].alive = false;
			change_state();
		}
	}

	if ( player_1.player1_laser[0].alive == true && check_collision(box, player_1.player1_laser[0].box) && alive == true )
	{
		change_state();
		if ( GAME_STATE == VERSUS )
			{
				o_player2_score.add_score(100);
			}
	}

	if ( player_2.player1_laser[0].alive == true && check_collision(box, player_2.player1_laser[0].box) && alive == true )
	{
		change_state();
	}

	if ( player_1.o_nuke->alive() == true && check_collision(box, player_1.o_nuke->box) && alive == true )
	{
		change_state();
		if ( GAME_STATE == VERSUS )
			{
				o_player2_score.add_score(100);
			}
	}

	if ( player_2.o_nuke->alive() == true && check_collision(box, player_2.o_nuke->box) && alive == true )
	{
		change_state();
	}

	if ( player_1.o_blast[0].alive() == true && check_collision(box, player_1.o_blast[0].box) && alive == true )
	{
		change_state();
		if ( GAME_STATE == VERSUS )
			{
				o_player2_score.add_score(100);
			}
	}

	if ( player_2.o_blast[0].alive() == true && check_collision(box, player_2.o_blast[0].box) && alive == true )
	{
		change_state();
	}

	if  ( o_player2_attacker.o_bulet[0].alive == true && check_collision(box, o_player2_attacker.o_bulet[0].box ) && alive == true)
	{
		change_state();
		change_state();
		if ( o_player2_attacker.o_bulet[0].b_laser == false ) {o_player2_attacker.o_bulet[0].alive = false;}
		if ( GAME_STATE == VERSUS )
			{
				o_player2_score.add_score(100);
			}
	}
}

void Block::change_state()
{
	state++;

	switch ( state )
	{
	case 1: type = s_block01; break;
	case 2: type = s_block02; break;
	case 3: type = s_block03; break;
	case 4: type = s_block04; break;
	case 5: type = s_block05; break;
	case 6: type = s_block06; break;
	case 7: type = s_block07; break;
	}

	if ( state >= 8 )
	{
		alive = 0;
	}
}

void Block::heal()
{
	state--;

	if ( state < 0 )
	{
		state++;
	}

	switch ( state )
	{
	case 0: type = s_block00; break;
	case 1: type = s_block01; break;
	case 2: type = s_block02; break;
	case 3: type = s_block03; break;
	case 4: type = s_block04; break;
	case 5: type = s_block05; break;
	case 6: type = s_block06; break;
	case 7: type = s_block07; break;
	}

}

void Block::show()
{
	if ( alive == true ) {apply_surface ( box.x, box.y, type, screen, NULL ); if ( o_bulet[0].alive == true ) { o_bulet[0].show();}}	
}

void Block::do_logic(Uint32 delta)
{
	if ( o_bulet[0].alive == true )
	{
		o_bulet[0].move(delta);
	}

	if ( alive == true )
	{
		shot();
	}
}


//Blocks
Blocks::Blocks()
{
	for ( int b = 0; b < 5; b++ )
	{
		o_Block.push_back(Block());
	}

	b_shot = false;
}


void Blocks::do_logic(Uint32 delta)
{
	for ( int b = 0; b < 5; b++ )
	{
		o_Block[b].do_logic(delta);
	}

	shot();
}

void Blocks::shot()
{
	if ( b_shot == true )
	{
	for ( int b = 0; b < 5; b++ )
	{
		o_Block[b].allow_shot();
	
		
	}
	b_shot = false;
	}

}

void Blocks::create_blocks()
{
	int X = 170;
	int Y = 400;

	for ( int b = 0; b < 5; b++ )
	{
		o_Block[b].create(X,Y);
		
		X += 100;
	}
}

void Blocks::show_blocks()
{
	for ( int b = 0; b < 5; b++ )
	{
		o_Block[b].show();
	}
}

void Blocks::check_bulets()
{
	for ( int b = 0; b < (int)o_Block.size(); b++ )
	{
		o_Block[b].check_bulet();
	}
}