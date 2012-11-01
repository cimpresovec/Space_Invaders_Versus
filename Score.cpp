#include <string>
#include <cstdlib>
#include <sstream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "Objects.h"
#include "Globals.h"
#include "Functions.h"
#include "Classes.h"

using namespace std;

Score::Score()
{
	i_score = 0;
	i_addscore = 0;

	i_x = 0;
	i_y = 0;

	i_time = 0;

	i_timer_score = 0;
}

void Score::set_up( int X, int Y)
{
	i_x = X;
	i_y = Y;
}

void Score::raise_score(int pl)
{
	if ( pl == 1 )
	{
		i_time += (int)(60*(delta.get_ticks() / 1000.f));

		if ( i_time > 40 )
		{
			i_score += 10;
			i_time = 0;
		}
	}	

	if ( pl == 2 )
	{
		i_time += (int)(60*(delta.get_ticks() / 1000.f));

		if ( i_time > 10 )
		{
			i_score += 10;
			i_time = 0;
		}
	}

}


void Score::show_score( int player )
{
	switch ( player )
	{
	case 1:
		{
			if ( o_player1_score.i_addscore != 0 ) { apply_surface( i_x + 20, i_y + 40, s_player1_addscore, screen, NULL ); }
			apply_surface( i_x, i_y, s_player1_score, screen, NULL ) ;
			break;
		}

	case 2:
		{
			if ( o_player2_score.i_addscore != 0 ) { apply_surface( 700 - s_player2_addscore->w , i_y + 40, s_player2_addscore, screen, NULL ); }
			apply_surface( 700 - s_player2_score->w , i_y, s_player2_score, screen, NULL ) ;
			break;
		}
	}
}

void Score::add_score(int addition)
{
	i_timer_score = 0;
	i_addscore += (int)( i_addscore * 0.05 );
	i_addscore += addition;
}

void Score::change_score(int set)
{
	i_score += set;
}

int Score::get_score()
{
	return i_score;
}

void Score::set_score()
{
	if ( i_addscore > 0 )
	{
		i_score += 100;
		i_addscore -= 100;
	}

	else { i_addscore = 0; }
}

void Score::render_score( int player )
{
	std::stringstream stream;
	std::stringstream stream1;

	switch ( player )
	{
	case 1:
		{
			stream << i_score;

			s_player1_score = TTF_RenderText_Solid(f_score, stream.str().c_str(), col_red);

			stream1 << "+" << i_addscore;

			s_player1_addscore = TTF_RenderText_Solid(f_score, stream1.str().c_str(), col_red);
		}

	case 2:
		{
			stream << i_score;

			if ( GAME_STATE == VERSUS )
			{
			s_player2_score = TTF_RenderText_Solid(f_score, stream.str().c_str(), col_black);
			}

			else { s_player2_score = TTF_RenderText_Solid(f_score, stream.str().c_str(), col_green); }

			stream1 << "+" << i_addscore;

			if ( GAME_STATE == VERSUS )
			{
				s_player2_addscore = TTF_RenderText_Solid(f_score, stream1.str().c_str(), col_black);}

			else
			{
				s_player2_addscore = TTF_RenderText_Solid(f_score, stream1.str().c_str(), col_green);}
		}
	}
}

void Score::score_logic()
{
	o_player1_score.i_timer_score += (int)(60*(delta.get_ticks() / 1000.f));
	o_player2_score.i_timer_score += (int)(60*(delta.get_ticks() / 1000.f));

	if ( o_player1_score.i_timer_score > 100 )
	{
		o_player1_score.set_score();
	}

	if ( o_player2_score.i_timer_score > 100 )
	{
		o_player2_score.set_score();
	}

	o_player1_score.render_score(1);
	o_player2_score.render_score(2);


}