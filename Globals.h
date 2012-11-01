#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "Functions.h"

using namespace std;

//Okno
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int SCREEN_BPP;

//FPS
extern const int FRAMES_PER_SECOND;

//Event
extern SDL_Event event;

//Font
extern TTF_Font * f_score;
extern TTF_Font * f_stats;

//Barva
extern SDL_Color col_red;
extern SDL_Color col_black;
extern SDL_Color col_green;

//Slike
extern SDL_Surface * screen;
extern SDL_Surface * background;
extern SDL_Surface * player1;
extern SDL_Surface * player2;
extern SDL_Surface * player1_shadow;
extern SDL_Surface * big_enemy;
extern SDL_Surface * medium_enemy1;
extern SDL_Surface * small_enemy1;
extern SDL_Surface * medium_enemy2;
extern SDL_Surface * small_enemy2;
extern SDL_Surface * bulet_frame0;
extern SDL_Surface * bulet_frame1;
extern SDL_Surface * s_block00;
extern SDL_Surface * s_block01;
extern SDL_Surface * s_block02;
extern SDL_Surface * s_block03;
extern SDL_Surface * s_block04;
extern SDL_Surface * s_block05;
extern SDL_Surface * s_block06;
extern SDL_Surface * s_block07;
extern SDL_Surface * s_player1_score;
extern SDL_Surface * s_player1_addscore;
extern SDL_Surface * s_player2_score;
extern SDL_Surface * s_player2_addscore;
extern SDL_Surface * s_select1;
extern SDL_Surface * s_p1power[];
extern SDL_Surface * s_blast[];
extern SDL_Surface * s_player1_bombs;
extern SDL_Surface * s_player1_shot;
extern SDL_Surface * s_player1_time;
extern SDL_Surface * s_player2_bombs;
extern SDL_Surface * s_player2_shot;
extern SDL_Surface * s_player2_time;
extern SDL_Surface * s_blockbulet;
extern SDL_Surface * s_nuke;
extern SDL_Surface * s_level_text;
extern SDL_Surface * s_level_speed;
extern SDL_Surface * s_menu;
extern SDL_Surface * s_attacker;
extern SDL_Surface * s_attacker_shot;
extern SDL_Surface * s_p2power[];
extern SDL_Surface * s_select2;
extern SDL_Surface * s_player2_acc;
extern SDL_Surface * s_player2_chance;
extern SDL_Surface * s_player2_time;
extern SDL_Surface * s_bigbulet;
extern SDL_Surface * s_biglaser;
extern SDL_Surface * s_player1_lives;
extern SDL_Surface * s_player2_lives;
extern SDL_Surface * s_win_screen;
extern SDL_Surface * s_game_over;
extern SDL_Surface * s_help;
extern SDL_Surface * s_p3power[];
extern SDL_Surface * s_locked;
extern SDL_Surface * s_site;
extern SDL_Surface * s_name;
extern SDL_Surface * s_high;

//Muzika
extern Mix_Music * m_menu;
extern Mix_Music * m_song1;
extern Mix_Music * m_song2;
extern Mix_Music * m_song3;
extern Mix_Chunk * m_explode;

//Konstante
const int TITLE = 0;
const int MENU = 1;
const int GAME = 2;
const int EXIT = 3;
const int VERSUS = 9;
const int SET_UP_VERSUS = 10;
const int SET_UP_NEW = 11;
const int SET_UP_TWO = 62;
const int GAME_2_PLAY = 63;
const int EXIT_TWO = 64;
const int LEFT = 4;
const int RIGHT = 5;
const int DOWN = 6;
const int LEVEL_CHANGE = 7;
const int WIN_SCREEN = 64;
const int GAME_OVER = 50;
const int SET_UP_CONT = 55;
const int HELP = 61;
const int SMALL_ENEMYS = 8;
const int MEDIUM_ENEMYS = 16;
const int BIG_ENEMYS = 16;
const int SCREEN_LEFT = 110;
const int SCREEN_RIGHT = 690;
const int EXIT_VERSUS = 56;
const int LOSE_TWO = 58;
const int EXIT_GAME = 57;
const int LEVEL_CHANGE_TWO = 59;
extern int CHANCE;



//Game state
extern int GAME_STATE;
extern int STATE_SET;

//Variable za objekte
extern int PLAYER_SPEED;
extern int BULET_SPEED;

#endif
