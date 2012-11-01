#include <string>
#include <cstdlib>
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "Globals.h"
#include "Functions.h"
#include "Classes.h"
#include "Objects.h"

using namespace std;

//Enemy Control
EnemyControl::EnemyControl()
{

	speed = 1000;

	i_bulet = 0;

	i_sound = 0;

	acceleration = 5;

	b_ammo = false;

	direction = RIGHT;

	//SmallEnemy
	for ( e1 = 0; e1 < SMALL_ENEMYS; e1++ )
	{
		//Naredi
		smallEnemy.push_back(Enemy());

	}

	//MediumEnemy
	for ( e2 = 0; e2 < MEDIUM_ENEMYS; e2++ )
	{
		//Naredi
		mediumEnemy.push_back(Enemy());

	}

	//Vsi big enemy
	for ( e3 = 0; e3 < BIG_ENEMYS; e3++ )
	{
		//Naredi
		bigEnemy.push_back(Enemy());
	}

	for ( int b = 0; b < 20; b++ )
	{
		o_bulet.push_back(Bulet());
	}

}

void EnemyControl::create_enemys()
{

	speed = 1000;

	X = 175;
	Y = 50;

	for ( e1 = 0; e1 < SMALL_ENEMYS; e1++ )
	{
		//Naredi
		smallEnemy[e1].set_up(X, Y, small_enemy1);

		smallEnemy[e1].x = X;
		smallEnemy[e1].y = Y;
		smallEnemy[e1].i_myY = Y;

		X += 65;
	}
		
	X = 175;
	Y = 85;

	//MediumEnemy
	for ( e2 = 0; e2 < MEDIUM_ENEMYS; e2++ )
	{
		//Naredi
		mediumEnemy[e2].set_up( X, Y, medium_enemy1 );

		//Èe je pri 8 sovražniku premakni v 2 vrsto
		if ( e2 == 8 )
		{
			Y = 120;
			X = 175;
		}

		mediumEnemy[e2].x = X;
		mediumEnemy[e2].y = Y;
		mediumEnemy[e2].i_myY = Y;

		//x nay bo vedno za 60 veè, tako bodo lepo razvršèeni
		X += 65;
	}

	X = 175;
	Y = 155;

	//Vsi big enemy
	for ( int e3 = 0; e3 < BIG_ENEMYS; e3++ )
	{
		//Naredi
		bigEnemy[e3].set_up( X, Y, big_enemy);

		//Èe je pri 8 sovražniku premakni v 2 vrsto
		if ( e3 == 8 )
		{
			Y = 190;
			X = 175;
		}

		bigEnemy[e3].x = X;
		bigEnemy[e3].y = Y;
		bigEnemy[e3].i_myY = Y;

		//x nay bo vedno za 60 veè, tako bodo lepo razvršèeni
		X += 65;
	}

	for ( int bu = 0; bu < o_bulet.size(); bu++ )
	{
		o_bulet[bu].alive = false;
	}
}

//Animacija sovražnikov in preverjanje kolizije
void EnemyControl::animate_enemy()
{
	for ( e1 = 0; e1 < SMALL_ENEMYS; e1++ )
	{
		smallEnemy[e1].animate(1);
	}

	for ( e2 = 0; e2 < MEDIUM_ENEMYS; e2++ )
	{
		mediumEnemy[e2].animate(2);
	}
}

//Premikanje
void EnemyControl::move_enemy()
{
	//Premakni nasprotnike odvosno od kam se premikajo
	if ( direction == LEFT )
	{
		for ( e1 = 0; e1 < SMALL_ENEMYS; e1++ )
		{
			smallEnemy[e1].x -= 10;

			if ( smallEnemy[e1].alive == true && smallEnemy[e1].x <= SCREEN_LEFT  )
			{
				pre_direction = RIGHT;
				direction = DOWN;
			}
		}

		for ( e2 = 0; e2 < MEDIUM_ENEMYS; e2++ )
		{
			mediumEnemy[e2].x -= 10;

			if ( mediumEnemy[e2].alive == true && mediumEnemy[e2].x <= SCREEN_LEFT )
			{
				pre_direction = RIGHT;
				direction = DOWN;
			}
		}

		for ( e3 = 0; e3 < BIG_ENEMYS; e3++ )
		{
			bigEnemy[e3].x -= 10;

			if ( bigEnemy[e3].alive == true && bigEnemy[e3].x <= SCREEN_LEFT )
			{
				pre_direction = RIGHT;
				direction = DOWN;
			}
		}
	}

	else if ( direction == RIGHT )
	{
		for ( e1 = 0; e1 < SMALL_ENEMYS; e1++ )
		{
			smallEnemy[e1].x += 10;

			//Èe je blizi desnega konca
			if ( smallEnemy[e1].alive == true && smallEnemy[e1].x + 50 >= SCREEN_RIGHT )
			{
				pre_direction = LEFT;
				direction = DOWN;
			}	
		}

		for ( e2 = 0; e2 < MEDIUM_ENEMYS; e2++ )
		{
			mediumEnemy[e2].x += 10;

			if ( mediumEnemy[e2].alive == true && mediumEnemy[e2].x + 50 >= SCREEN_RIGHT )
			{
				pre_direction = LEFT;
				direction = DOWN;
			}
		}

		for ( e3 = 0; e3 < BIG_ENEMYS; e3++ )
		{
			bigEnemy[e3].x += 10;

			if ( bigEnemy[e3].alive == true && bigEnemy[e3].x + 50 >= SCREEN_RIGHT )
			{
				pre_direction = LEFT;
				direction = DOWN;
			}
		}
	}

	else if ( direction == DOWN )
	{
		for ( e1 = 0; e1 < SMALL_ENEMYS; e1++ )
		{
			smallEnemy[e1].y += 10;	
			smallEnemy[e1].i_myY += 10;
		}

		for ( e2 = 0; e2 < MEDIUM_ENEMYS; e2++ )
		{
			mediumEnemy[e2].y += 10;
			mediumEnemy[e2].i_myY += 10;
		}

		for ( e3 = 0; e3 < BIG_ENEMYS; e3++ )
		{
			bigEnemy[e3].y += 10;
			bigEnemy[e3].i_myY += 10;
		}

		direction = pre_direction;
	}
}

void EnemyControl::check_collisions()
{
	for ( e1 = 0; e1 < SMALL_ENEMYS; e1++ )
	{
		if ( smallEnemy[e1].check_bulet() == true ) 
		{ 
			o_player1_score.add_score(500);
		} 

		if ( smallEnemy[e1].check_bulet2() == true ) 
		{ 
			o_player2_score.add_score(500);
		} 
	}

	for ( e2 = 0; e2 < MEDIUM_ENEMYS; e2++ )
	{
		if ( mediumEnemy[e2].check_bulet() == true ) 
		{ 
			o_player1_score.add_score(250);
		} 

		if ( mediumEnemy[e2].check_bulet2() == true ) 
		{ 
			o_player2_score.add_score(250);
		} 
	}

	for ( e3 = 0; e3 < BIG_ENEMYS; e3++ )
	{
		if ( bigEnemy[e3].check_bulet() == true ) { o_player1_score.add_score(100); } 
		if ( bigEnemy[e3].check_bulet2() == true ) { o_player2_score.add_score(100); } 
	}
}



//Prikaz nasprotnikov
void EnemyControl::show_enemy()
{
	for ( e1 = 0; e1 < SMALL_ENEMYS; e1++ )
	{
		if ( smallEnemy[e1].alive == true )
		{
			smallEnemy[e1].show();
		}
	}

	for ( e2 = 0; e2 < MEDIUM_ENEMYS; e2++ )
	{
		if ( mediumEnemy[e2].alive == true )
		{
			mediumEnemy[e2].show();
		}
	}

	for ( e3 = 0; e3 < BIG_ENEMYS; e3++ )
	{
		if ( bigEnemy[e3].alive == true )
		{
			bigEnemy[e3].show();
		}
	}

	for ( int b = 0; b < (int)o_bulet.size(); b++ )
	{
		if ( o_bulet[b].alive == true )
		{
			o_bulet[b].show();
		}
	}
}

void EnemyControl::enemy_shot()
{
	//Kolikšna je šansa da strelja
	int chance = ( rand() % CHANCE ) + 1;

	if ( chance == 15 )
	{
		//Izbere vrsto za strelaje
		int line = ( rand() % 8 ) + 1;

		switch ( line )
		{
		case 1:
			{
				if ( bigEnemy[8].alive == true ) { create_bulet( bigEnemy[8].box ); break; }
				else if ( bigEnemy[0].alive == true ) { create_bulet( bigEnemy[0].box ); break; }
				else if ( mediumEnemy[8].alive == true ) { create_bulet( mediumEnemy[8].box ); break; }
				else if ( mediumEnemy[0].alive == true ) { create_bulet( mediumEnemy[0].box ); break; }
				else if ( smallEnemy[0].alive == true ) { create_bulet( smallEnemy[0].box ); break; }
				else { line++; }
			}

		case 2:
			{
				if ( bigEnemy[9].alive == true ) { create_bulet( bigEnemy[9].box ); break; }
				else if ( bigEnemy[1].alive == true ) { create_bulet( bigEnemy[1].box ); break; }
				else if ( mediumEnemy[9].alive == true ) { create_bulet( mediumEnemy[9].box ); break; }
				else if ( mediumEnemy[1].alive == true ) { create_bulet( mediumEnemy[1].box ); break; }
				else if ( smallEnemy[1].alive == true ) { create_bulet( smallEnemy[1].box ); break; }
				else { line++; }
			}

		case 3:
			{
				if ( bigEnemy[10].alive == true ) { create_bulet( bigEnemy[10].box ); break; }
				else if ( bigEnemy[2].alive == true ) { create_bulet( bigEnemy[2].box ); break; }
				else if ( mediumEnemy[10].alive == true ) { create_bulet( mediumEnemy[10].box ); break; }
				else if ( mediumEnemy[2].alive == true ) { create_bulet( mediumEnemy[2].box ); break; }
				else if ( smallEnemy[2].alive == true ) { create_bulet( smallEnemy[2].box ); break; }
				else { line++; }
			}

		case 4:
			{
				if ( bigEnemy[11].alive == true ) { create_bulet( bigEnemy[11].box ); break; }
				else if ( bigEnemy[3].alive == true ) { create_bulet( bigEnemy[3].box ); break; }
				else if ( mediumEnemy[11].alive == true ) { create_bulet( mediumEnemy[11].box ); break; }
				else if ( mediumEnemy[3].alive == true ) { create_bulet( mediumEnemy[3].box ); break; }
				else if ( smallEnemy[3].alive == true ) { create_bulet( smallEnemy[3].box ); break; }
				else { line++; }
			}

		case 5:
			{
				if ( bigEnemy[12].alive == true ) { create_bulet( bigEnemy[12].box ); break; }
				else if ( bigEnemy[4].alive == true ) { create_bulet( bigEnemy[4].box ); break; }
				else if ( mediumEnemy[12].alive == true ) { create_bulet( mediumEnemy[12].box ); break; }
				else if ( mediumEnemy[4].alive == true ) { create_bulet( mediumEnemy[4].box ); break; }
				else if ( smallEnemy[4].alive == true ) { create_bulet( smallEnemy[4].box ); break; }
				else { line++; }
			}

		case 6:
			{
				if ( bigEnemy[13].alive == true ) { create_bulet( bigEnemy[13].box ); break; }
				else if ( bigEnemy[5].alive == true ) { create_bulet( bigEnemy[5].box ); break; }
				else if ( mediumEnemy[13].alive == true ) { create_bulet( mediumEnemy[13].box ); break; }
				else if ( mediumEnemy[5].alive == true ) { create_bulet( mediumEnemy[5].box ); break; }
				else if ( smallEnemy[5].alive == true ) { create_bulet( smallEnemy[5].box ); break; }
				else { line++; }
			}

		case 7:
			{
				if ( bigEnemy[14].alive == true ) { create_bulet( bigEnemy[14].box ); break; }
				else if ( bigEnemy[6].alive == true ) { create_bulet( bigEnemy[6].box ); break; }
				else if ( mediumEnemy[14].alive == true ) { create_bulet( mediumEnemy[14].box ); break; }
				else if ( mediumEnemy[6].alive == true ) { create_bulet( mediumEnemy[6].box ); break; }
				else if ( smallEnemy[6].alive == true ) { create_bulet( smallEnemy[6].box ); break; }
				else { line++; }
			}

		case 8:
			{
				if ( bigEnemy[15].alive == true ) { create_bulet( bigEnemy[15].box ); break; }
				else if ( bigEnemy[7].alive == true ) { create_bulet( bigEnemy[7].box ); break; }
				else if ( mediumEnemy[15].alive == true ) { create_bulet( mediumEnemy[15].box ); break; }
				else if ( mediumEnemy[7].alive == true ) { create_bulet( mediumEnemy[7].box ); break; }
				else if ( smallEnemy[7].alive == true ) { create_bulet( smallEnemy[7].box ); break; }
			}
		}
	}
}

void EnemyControl::create_bulet(SDL_Rect place)
{
	if ( b_ammo == true )
	{
		o_bulet[i_bulet].create( place.x + 15, place.y + 25 );
		o_bulet[i_bulet].yVel -= (BULET_SPEED + BULET_SPEED);
		o_bulet[i_bulet].bulet_surface = s_bigbulet;
		o_bulet[i_bulet].box.w = 25;
		o_bulet[i_bulet].box.h = 25;
		o_bulet[i_bulet].frame = 3;
	}

	else
	{
	o_bulet[i_bulet].create( place.x + 20, place.y + 25 );
	o_bulet[i_bulet].yVel -= (BULET_SPEED + BULET_SPEED);
	o_bulet[i_bulet].box.w = 20;

	}
	i_bulet++;

	if ( i_bulet >= 19 )
	{
		i_bulet = 0;
	}


}

void EnemyControl::check_bulet_player()
{
	for ( int b = 0; b < (int)o_bulet.size(); b++ )
	{
		if ( o_bulet[b].alive == true )
		{
			if ( check_collision(o_bulet[b].box, player_1.box) )
			{
				o_bulet[b].alive = false;
				if ( player_1.get_lives() > 0 )
				{
					player_1.set_lives(-1);
				}

			}

			if ( check_collision(o_bulet[b].box, player_2.box) )
			{
				o_bulet[b].alive = false;
				if ( player_2.get_lives() > 0 )
				{
					player_2.set_lives(-1);
				}

			}

			for ( int g = 0; g < (int)blocks.o_Block.size(); g++ )
			{
				if ( check_collision(o_bulet[b].box, blocks.o_Block[g].box ) && blocks.o_Block[g].alive == true )
				{
					o_bulet[b].alive = false;
					blocks.o_Block[g].change_state();
					if ( GAME_STATE == VERSUS )
					{
						o_player2_score.add_score(100);
					}
				}
			}
		}
	}
}

bool EnemyControl::make_new()
{
	for ( int s = 0; s < SMALL_ENEMYS; s++ )
	{
		if ( smallEnemy[s].alive == false )
		{
			smallEnemy[s].make_me();
			return true;
		}
	}

	for ( int m = 0; m < BIG_ENEMYS; m++ )
	{
		if ( mediumEnemy[m].alive == false )
		{
			mediumEnemy[m].make_me();
			return true;
		}

		if ( bigEnemy[m].alive == false )
		{
			bigEnemy[m].make_me();
			return true;
		}
	}

	return false;
}

bool EnemyControl::sacrifice()
{

	for ( int s = 0; s < SMALL_ENEMYS; s++ )
	{
		if ( smallEnemy[s].alive == true )
		{
			o_player2_score.change_score(500);
			smallEnemy[s].alive = false;
			return true;
		}
	}

	for ( int m = 0; m < BIG_ENEMYS; m++ )
	{

		if ( mediumEnemy[m].alive == true )
		{
			mediumEnemy[m].alive = false;
			o_player2_score.change_score(400);
			return true;
		}

		if ( bigEnemy[m].alive == true )
		{
			bigEnemy[m].alive = false;
			o_player2_score.change_score(300);
			return true;
		}
	}

	

	return false;

}

bool EnemyControl::check_dead()
{
	for ( int s = 0; s < SMALL_ENEMYS; s++ )
	{

		if ( smallEnemy[s].alive == true ) 
		{
			return false;
		}
		
	}

	for ( int m = 0; m < BIG_ENEMYS; m++ )
	{
		
		if ( mediumEnemy[m].alive == true || bigEnemy[m].alive == true )
		{
			return false;
		}
	}

	return true;
}

bool EnemyControl::check_down()
{
	for ( int s = 0; s < SMALL_ENEMYS; s++ )
	{
		if ( smallEnemy[s].y >= 470 && smallEnemy[s].alive == true )
		{
			return true;
		}		
	}

	for ( int m = 0; m < BIG_ENEMYS; m++ )
	{
		if ( mediumEnemy[m].y >= 470 && mediumEnemy[m].alive == true )
		{
			return true;
		}

		if ( bigEnemy[m].y >= 470 && bigEnemy[m].alive == true )
		{
			return true;
		}
	}

	return false;

}

//Logika
void EnemyControl::do_logic( int time )
{	
	check_collisions();
	check_bulet_player();
	

	for ( int b = 0; b < (int)o_bulet.size(); b++ )
	{
		if ( o_bulet[b].alive == true )
		{
			o_bulet[b].move(delta.get_ticks());
		}
	}

	if ( time > speed )
	{
		//Animiraj in premakni sovražnike
		animate_enemy();
		move_enemy();
		
		
		enemyMovement.start();

		if ( speed > 100 ) { speed -= acceleration; }
	}

	if ( check_dead() == true ) 
	{ 
		if ( GAME_STATE == VERSUS )
		{
			STATE_SET = WIN_SCREEN;
		}

		if ( GAME_STATE == GAME )
		{
			STATE_SET = LEVEL_CHANGE;
		}

		if ( GAME_STATE == GAME_2_PLAY )
		{
			STATE_SET = LEVEL_CHANGE_TWO;
		}
	}

	if ( check_down() == true )
	{
		if ( GAME_STATE == GAME )
		{
			STATE_SET = GAME_OVER;
		}

		if ( GAME_STATE == GAME_2_PLAY )
		{
			STATE_SET = LOSE_TWO;
		}
	}
}