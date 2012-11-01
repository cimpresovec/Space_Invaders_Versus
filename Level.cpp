#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
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

Level::Level()
{
	i_level = NULL;
}

void Level::get_level( int yes )
{
	std::fstream load ("data/save.txt");

	string level;

	getline(load, level);

	i_level = atoi(level.c_str());

	//load.ignore();

	string al[8];
	

	for ( int s = 0; s < 8; s++ )
	{
		stringstream m;
		int sl = 0;

		getline(load, al[s] );
		sl = atoi(al[s].c_str());

		if ( sl == 1 )
		{
			o_player1_buy.b_unlocked[s] = true;
		}

		else {
			o_player1_buy.b_unlocked[s] = false;
		}

		cout << sl << endl;

		if ( sl == 1 )
		{
			m << "data/gfx/p1_power" << s << ".png";
			s_p1power[s] = load_image(m.str());
		}
	}

	if ( yes == 1 )
	{
		int score = 0;
		string scores;
		getline(load, scores);

		score = atoi(scores.c_str());

		o_player1_score.change_score(-o_player1_score.get_score());
		o_player1_score.change_score(score);
	}

	string lives;
	int liv;

	getline(load, lives);

	liv = atoi(lives.c_str());

	player_1.i_lives = liv;

	string high;
	int highs;

	getline(load, high);

	highs = atoi(high.c_str());

	i_high_level = highs;

	cout << highs << endl;

	load.close();
}


void Level::set_difficulity()
{
	enemycontrol.acceleration = 5 + 2 * i_level;
	if ( enemycontrol.acceleration > 15 ) 
	{
		enemycontrol.acceleration = 15;
	}

	CHANCE -= i_level;
	if ( CHANCE < 15 )
	{ CHANCE = 15; }
}

void Level::render_level()
{
	stringstream text;

	text << "Lvl " << i_level;

	s_level_text = TTF_RenderText_Solid(f_score, text.str().c_str(), col_black);

	/*stringstream speed;
	speed << enemycontrol.acceleration;

	s_level_speed = TTF_RenderText_Solid(f_score, speed.str().c_str(), col_black);*/
}

void Level::show()
{
	apply_surface( ( 800 - s_level_text->w ) / 2, 550, s_level_text, screen, NULL);
	//apply_surface( ( 800 - s_level_speed->w) / 2, 510, s_level_speed, screen, NULL);
}

void Level::save_level()
{
	std::ofstream save ( "data/save.txt");

	save << i_level << endl;

	for ( int s = 0; s < 8; s++ )
	{
		save << o_player1_buy.b_unlocked[s] << endl;
	}

	save << o_player1_score.get_score() << endl;

	save << player_1.i_lives << endl;

	save << i_high_level << endl;

	save.close();
}
