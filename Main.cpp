/* Space Invaders Versus je predelava igre Space Invaders. 
Narejena bo v glavnem za 2 igralca, verjetno pa bo vkluèena možnost za1 igralca.
Igra bo vsebovala kar veliko stvari in to je kar velik projekt.

Programer: Luka Horvat
Datum: 26. 1. 2009
*/


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

//Main
int main ( int argc, char* args[] )
{
	//Èe je vse ok
	if ( init() == false )
	{
		return 1;
	}

	if ( load_files() == false )
	{
		return 1;
	}

	//Exit
	bool exit = false;

	Mix_PlayMusic(m_song1, 0);
	m_explode->volume = 10;

	int times = 0;

	srand(time(NULL));

	//Naredi sovražnike
	enemycontrol.create_enemys();

	blocks.create_blocks();

	o_player1_score.set_up(100,510);
	o_player2_score.set_up(600,510);

	//o_player1_score.change_score(50000);


	//Zagni delta
	delta.start();

	enemyMovement.start();

	o_level.get_level(1);

	//Zagni vse
	while ( exit == false )
	{
		//Zagni fps
		FPS.start();

				if ( event.type == SDL_KEYDOWN )
				{
					switch ( event.key.keysym.sym )
					{
					case SDLK_1: Mix_PlayMusic(m_song1, -1); break;
					case SDLK_2: Mix_PlayMusic(m_song2, -1); break;
					case SDLK_3: Mix_PlayMusic(m_song3, -1); break;
					}
				}
		

		//Title
		if ( GAME_STATE == TITLE )
		{

		}
		
		//Menu
		if ( GAME_STATE == MENU )
		{
			while ( SDL_PollEvent(&event) )
			{
				///////////EVENTI///////////
				

				//Exit
				if ( event.type == SDL_KEYUP )
				{
					if ( event.key.keysym.sym == SDLK_ESCAPE )
					{
						STATE_SET = EXIT;
					}

				}

				if ( event.type == SDL_MOUSEBUTTONUP )
				{
					/// 2play: 65, 300, 325, 365  exit: 250 480 500 555		
					if ( event.motion.x > 420 && event.motion.x < 680 && event.motion.y > 200 && event.motion.y < 270 )
					{
						STATE_SET = SET_UP_CONT;
					}

					if ( event.motion.x > 65 && event.motion.x < 325 && event.motion.y > 200 && event.motion.y < 270 )
					{
						
						STATE_SET = SET_UP_NEW;	
					}

					if ( event.motion.x > 420 && event.motion.x < 680 && event.motion.y > 300 && event.motion.y < 365 )
					{
						
						STATE_SET = SET_UP_VERSUS;	
					}

					if ( event.motion.x > 200 && event.motion.x < 560 && event.motion.y > 390 && event.motion.y < 460 )
					{
						
						STATE_SET = HELP;	
					}

					if ( event.motion.x > 250 && event.motion.x < 500 && event.motion.y > 480 && event.motion.y < 555 )
					{
						
						STATE_SET = EXIT;	
					}

					if ( event.motion.x > 65 && event.motion.x < 325 && event.motion.y > 300 && event.motion.y < 365 )
					{
						
						STATE_SET = SET_UP_TWO;	
					}

				}
			}
			
			s_site = TTF_RenderText_Solid(f_stats, "http://red-dev.co.nr", col_red);
			s_name = TTF_RenderText_Solid(f_stats, "by: Luka Horvat", col_red);

			apply_surface(0,0, s_menu, screen, NULL);
			apply_surface(105, 570, s_site, screen, NULL);
			apply_surface( 695 - s_name->w, 570, s_name, screen, NULL);
			SDL_Flip(screen);

		}

		if ( GAME_STATE == LEVEL_CHANGE )
		{
			o_level.save_level();
			o_level.get_level(1);
			o_level.i_level += 1;
			o_level.save_level();

			enemycontrol.create_enemys();
			o_level.set_difficulity();
			player_1.b_super = true;
		
			STATE_SET = GAME;
		}

		if ( GAME_STATE == LEVEL_CHANGE_TWO )
		{
             //int liv = player_1.i_lives;
			//o_level.get_level(1);
			o_level.i_level += 1;
			//player_1.i_lives = liv;

			enemycontrol.create_enemys();
			o_level.set_difficulity();
			player_1.b_super = true;
			player_2.b_super = true;
		
			STATE_SET = GAME_2_PLAY;
		}

		if ( GAME_STATE == SET_UP_VERSUS )
		{
			o_player1_buy.unlock();
			o_player1_score.change_score(-o_player1_score.get_score());
			o_player1_score.i_addscore = 0;
			o_player2_score.change_score(-o_player2_score.get_score());
			o_player2_score.i_addscore = 0;
			enemycontrol.create_enemys();
			blocks.create_blocks();
			player_1.clean_up();
			player_1.i_lives = 5;
			STATE_SET = VERSUS;
		}

		if ( GAME_STATE == SET_UP_TWO )
		{
			o_level.i_level = 1;
			o_level.set_difficulity();
			player_1.b_super = true;
			player_2.b_super = true;
			o_player1_buy.reset();
			o_player1_score.change_score(-o_player1_score.get_score());
			o_player1_score.i_addscore = 0;
			o_player2_buy.reset();
			o_player2_score.change_score(-o_player2_score.get_score());
			o_player2_score.i_addscore = 0;
			enemycontrol.create_enemys();
			blocks.create_blocks();
			
			player_1.clean_up();
			player_1.i_lives = 5;
			player_2.clean_up();
			player_2.set_up();
			player_2.i_lives = 5;
			o_player2_buy.set_up();
			//o_player2_score.change_score(200000);

			STATE_SET = GAME_2_PLAY;

		}

		if ( GAME_STATE == SET_UP_NEW )
		{
			o_level.i_level = 1;
			o_level.set_difficulity();player_1.b_super = true;
			o_player1_buy.reset();
			o_player1_score.change_score(-o_player1_score.get_score());
			o_player1_score.i_addscore = 0;
			enemycontrol.create_enemys();
			blocks.create_blocks();
		
			player_1.clean_up();
			player_1.i_lives = 5;
			o_level.save_level();
			STATE_SET = GAME;
		}

		if ( GAME_STATE == EXIT_TWO )
		{
			player_1.clean_up();
			player_2.clean_up();
			o_level.get_level(1);

			STATE_SET = MENU;
		}

		if ( GAME_STATE == HELP )
		{
			if ( SDL_PollEvent(&event) )
			{
				if ( event.type == SDL_KEYUP )
				{
					STATE_SET = MENU;
				}
			}
		
			stringstream he;
			he << "Highscore: lvl " << o_level.i_high_level;
			s_high = TTF_RenderText_Solid(f_score, he.str().c_str(), col_red);
			apply_surface(0,0, s_help, screen, NULL);
			apply_surface(400, 550, s_high, screen,NULL); 

			SDL_Flip(screen);
		}

		if ( GAME_STATE == SET_UP_CONT )
		{
			
			blocks.create_blocks();
			enemycontrol.create_enemys();
			player_1.clean_up();
			o_level.get_level(1);
			o_level.set_difficulity();
			player_1.b_super = true;
			o_player1_score.i_addscore = 0;
			STATE_SET = GAME;
		}

		if ( GAME_STATE == GAME_OVER )
		{
			s_win_screen = load_image("data/gfx/game_over.png");

			if ( SDL_PollEvent(&event) )
			{
				if ( event.type == SDL_KEYUP )
				{
					STATE_SET = EXIT_GAME;

					o_level.save_level();
					if ( o_level.i_level > o_level.i_high_level )
					{
						o_level.i_high_level = o_level.i_level;
					}
					o_level.i_level = 1;
					o_player1_score.change_score(-o_player1_score.get_score());
					o_player1_score.i_addscore = 0;
					o_level.save_level();

				}
			}
				

		


			apply_surface(0,0, s_win_screen, screen, NULL);
			SDL_Flip(screen);
		}

		if ( GAME_STATE == LOSE_TWO )
		{
			s_win_screen = load_image("data/gfx/game_over.png");

			if ( SDL_PollEvent(&event) )
			{
				if ( event.type == SDL_KEYUP )
				{
					STATE_SET = EXIT_TWO;		
				}
			}
				
			apply_surface(0,0, s_win_screen, screen, NULL);
			SDL_Flip(screen);
		}

		if ( GAME_STATE == WIN_SCREEN )
		{
			if ( player_1.get_lives() == 0 )
			{
				s_win_screen = load_image("data/gfx/player2_wins.png");
			}

			else { s_win_screen = load_image("data/gfx/player1_wins.png"); }


			if ( SDL_PollEvent(&event) )
			{
				if ( event.type == SDL_KEYUP )
				{
				
					STATE_SET = EXIT_VERSUS;
				}

			}

			apply_surface(0,0, s_win_screen, screen, NULL);
			SDL_Flip(screen);

		}


		//Igra
		if ( GAME_STATE == GAME )
		{
			while ( SDL_PollEvent(&event) )
			{
				///////////EVENTI///////////
				player_1.hande_input();

				o_player1_buy.handle_input();

				player_1.o_blast[0].button();

				player_1.blast();
				

				if ( event.type == SDL_KEYDOWN )
				{
					switch ( event.key.keysym.sym )
					{
					case SDLK_1: Mix_PlayMusic(m_song1, -1); break;
					case SDLK_2: Mix_PlayMusic(m_song2, -1); break;
					case SDLK_3: Mix_PlayMusic(m_song3, -1); break;
					}
				}

				//Exit
				if ( event.type == SDL_KEYUP )
				{
					if ( event.key.keysym.sym == SDLK_ESCAPE )
					{
						STATE_SET = EXIT_GAME;
					}
				}
			}

			////////////LOGIKA//////////////
			player_1.move(delta.get_ticks());
			player_1.shot();
			player_1.check_time();

			o_player1_score.score_logic();

			enemycontrol.do_logic(enemyMovement.get_ticks());
			enemycontrol.enemy_shot();

			blocks.check_bulets();
			blocks.do_logic(delta.get_ticks());

			o_player1_buy.move();
			o_player1_buy.buy();
		
			o_level.render_level();

			delta.start();

			///////////RENDERING/////////////
			apply_surface(0, 0, background, screen, NULL);

			enemycontrol.show_enemy();

			player_1.show();

			o_player1_buy.show();

			blocks.show_blocks();

			o_level.show();

			o_player1_score.show_score(1);
			//apply_surface(50,50, s_player1_time, screen, NULL);

			SDL_Flip(screen);
		}

		if ( GAME_STATE == GAME_2_PLAY )
		{
			while ( SDL_PollEvent(&event) )
			{
				///////////EVENTI///////////
				player_1.hande_input();
				player_2.hande_input();

				o_player1_buy.handle_input();
				o_player2_buy.handle_input();

				player_1.o_blast[0].button();

				player_1.blast();

				player_2.o_blast[0].button();

				player_2.blast();
				

				if ( event.type == SDL_KEYDOWN )
				{
					switch ( event.key.keysym.sym )
					{
					case SDLK_1: Mix_PlayMusic(m_song1, -1); break;
					case SDLK_2: Mix_PlayMusic(m_song2, -1); break;
					case SDLK_3: Mix_PlayMusic(m_song3, -1); break;
					}
				}

				//Exit
				if ( event.type == SDL_KEYUP )
				{
					if ( event.key.keysym.sym == SDLK_ESCAPE )
					{
						STATE_SET = EXIT_TWO;
					}
				}
			}

			////////////LOGIKA//////////////
			player_1.move(delta.get_ticks());
			player_1.shot();
			player_1.check_time();

			player_2.move(delta.get_ticks());
			player_2.shot();
			player_2.check_time();

			o_player1_score.score_logic();

			enemycontrol.do_logic(enemyMovement.get_ticks());
			enemycontrol.enemy_shot();

			blocks.check_bulets();
			blocks.do_logic(delta.get_ticks());

			o_player1_buy.move();
			o_player1_buy.buy();
			o_player2_buy.move();
			o_player2_buy.buy2();
		
			o_level.render_level();

			delta.start();

			///////////RENDERING/////////////
			apply_surface(0, 0, background, screen, NULL);

			enemycontrol.show_enemy();

			player_1.show();
			player_2.show();

			o_player1_buy.show();
			o_player2_buy.show();

			blocks.show_blocks();

			o_level.show();

			o_player1_score.show_score(1);
			o_player1_score.show_score(2);
			//apply_surface(50,50, s_player1_time, screen, NULL);

			SDL_Flip(screen);
		}

		if ( GAME_STATE == VERSUS )
		{
			while ( SDL_PollEvent(&event) )
			{
				///////////EVENTI///////////
				player_1.hande_input();

				o_player2_attacker.handle_input();

				o_player1_buy.handle_input();

				o_player3_buy.handle_input();

				player_1.o_blast[0].button();

				player_1.blast();
				

				if ( event.type == SDL_KEYDOWN )
				{
					switch ( event.key.keysym.sym )
					{
					case SDLK_1: Mix_PlayMusic(m_song1, -1); break;
					case SDLK_2: Mix_PlayMusic(m_song2, -1); break;
					case SDLK_3: Mix_PlayMusic(m_song3, -1); break;
					}
				}

				//Exit
				if ( event.type == SDL_KEYUP )
				{
					if ( event.key.keysym.sym == SDLK_ESCAPE )
					{
						STATE_SET = EXIT_VERSUS;
					}
				}
			}

			////////////LOGIKA//////////////
			player_1.move(delta.get_ticks());
			player_1.shot();
			player_1.check_time();

			o_player2_attacker.move(delta.get_ticks());
			o_player2_attacker.shot();

			o_player1_score.score_logic();

			enemycontrol.do_logic(enemyMovement.get_ticks());
			enemycontrol.enemy_shot();

			blocks.check_bulets();
			blocks.do_logic(delta.get_ticks());

			o_player1_buy.move();
			o_player1_buy.buy();

			o_player3_buy.move();
			o_player3_buy.buy();
		
			o_level.render_level();

			o_player1_score.raise_score(1);
			o_player2_score.raise_score(2);

			delta.start();

			///////////RENDERING/////////////
			apply_surface(0, 0, background, screen, NULL);

			enemycontrol.show_enemy();

			player_1.show();

			o_player2_attacker.show();

			o_player1_buy.show();

			o_player3_buy.show();

			blocks.show_blocks();

			o_level.show();

			o_player1_score.show_score(1);
			o_player2_score.show_score(2);
			//apply_surface(50,50, s_player1_time, screen, NULL);

			SDL_Flip(screen);
		
		}

		if ( GAME_STATE == EXIT_VERSUS )
		{			
			player_1.clean_up();
			o_level.get_level(1);

			STATE_SET = MENU;
		}

		if (GAME_STATE == EXIT_GAME )
		{
			o_player1_score.change_score(o_player1_score.i_addscore);
			o_level.save_level();

			STATE_SET = MENU;
		}

		//Exit
		if ( GAME_STATE == EXIT )
		{
			exit = true;
			
		}

		if ( FPS.get_ticks() < 1000 / FRAMES_PER_SECOND )
		{
			SDL_Delay( (1000 / FRAMES_PER_SECOND) - FPS.get_ticks() );
		}

		GAME_STATE = STATE_SET;
		
		
	}

	clean_up();
	return 0;
}
