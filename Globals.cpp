#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "Globals.h"
#include "Functions.h"
#include "Classes.h"

using namespace std;

using namespace std;

//Okno
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;

int CHANCE = 80;

//FPS
const int FRAMES_PER_SECOND = 60;

SDL_Event event;

//Font
TTF_Font * f_score = NULL;
TTF_Font * f_stats = NULL;

//barve
SDL_Color col_red = { 255,0,0};
SDL_Color col_black = { 0,0,0};
SDL_Color col_green = { 255, 0, 255 };

//Slike
SDL_Surface * screen = NULL;
SDL_Surface * background = NULL;
SDL_Surface * player1 = NULL;
SDL_Surface * player2 = NULL;
SDL_Surface * player1_shadow = NULL;
SDL_Surface * big_enemy = NULL;
SDL_Surface * medium_enemy1 = NULL;
SDL_Surface * medium_enemy2 = NULL;
SDL_Surface * small_enemy2 = NULL;
SDL_Surface * small_enemy1 = NULL;
SDL_Surface * bulet_frame0 = NULL;
SDL_Surface * bulet_frame1 = NULL;
SDL_Surface * s_block00 = NULL;
SDL_Surface * s_block01 = NULL;
SDL_Surface * s_block02 = NULL;
SDL_Surface * s_block03 = NULL;
SDL_Surface * s_block04 = NULL;
SDL_Surface * s_block05 = NULL;
SDL_Surface * s_block06 = NULL;
SDL_Surface * s_block07 = NULL;
SDL_Surface * s_player1_score = NULL;
SDL_Surface * s_player1_addscore = NULL;
SDL_Surface * s_player2_score = NULL;
SDL_Surface * s_player2_addscore = NULL;
SDL_Surface * s_select1 = NULL;
SDL_Surface * s_p1power[] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
SDL_Surface * s_p3power[] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
SDL_Surface * s_blast[] = { NULL, NULL, NULL };
SDL_Surface * s_player1_bombs = NULL;
SDL_Surface * s_player1_shot = NULL;
SDL_Surface * s_player1_time = NULL;
SDL_Surface * s_player2_bombs = NULL;
SDL_Surface * s_player2_shot = NULL;
SDL_Surface * s_blockbulet = NULL;
SDL_Surface * s_nuke = NULL;
SDL_Surface * s_level_text = NULL;
SDL_Surface * s_level_speed = NULL;
SDL_Surface * s_menu = NULL;
SDL_Surface * s_attacker = NULL;
SDL_Surface * s_attacker_shot = NULL;
SDL_Surface * s_p2power[] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
SDL_Surface * s_select2 = NULL;
SDL_Surface * s_player2_acc = NULL;
SDL_Surface * s_player2_chance = NULL;
SDL_Surface * s_player2_time = NULL;
SDL_Surface * s_bigbulet = NULL;
SDL_Surface * s_biglaser = NULL;
SDL_Surface * s_player1_lives = NULL;
SDL_Surface * s_player2_lives = NULL;
SDL_Surface * s_win_screen = NULL;
SDL_Surface * s_game_over = NULL;
SDL_Surface * s_help = NULL;
SDL_Surface * s_locked = NULL;
SDL_Surface * s_site = NULL;
SDL_Surface * s_name = NULL;
SDL_Surface * s_high = NULL;

//Muzika
Mix_Music * m_menu = NULL;
Mix_Music * m_song1 = NULL;
Mix_Music * m_song2 = NULL;
Mix_Music * m_song3 = NULL;
Mix_Chunk * m_explode = NULL;


//Game state
int GAME_STATE = MENU;
int STATE_SET = MENU;

//Variabli za objekte
int PLAYER_SPEED = 200;
int BULET_SPEED = -200;