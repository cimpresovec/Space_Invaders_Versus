#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
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

//Nalaganje
SDL_Surface * load_image ( string filename )
{
	SDL_Surface * loaded = NULL;
	SDL_Surface* optimized = NULL;

	loaded = IMG_Load(filename.c_str());
	
	if ( loaded != NULL )
	{
		optimized = SDL_DisplayFormat(loaded);

		SDL_FreeSurface(loaded);

		if ( optimized != NULL )
		{
			SDL_SetColorKey(optimized, SDL_SRCCOLORKEY, SDL_MapRGB(optimized->format, 0, 0xFF, 0xFF));
		}
	}

	return optimized;
}

//Risanje
void apply_surface ( int x, int y, SDL_Surface * src, SDL_Surface * dst, SDL_Rect * clip)
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(src, clip, dst, &offset);
}

//Nalaganje stvari
bool load_files()
{
	background = load_image("data/gfx/background.png");
	player1 = load_image("data/gfx/ship.png");
	player2 = load_image("data/gfx/ship2.png");
	player1_shadow = load_image("data/gfx/ship_shadow.png");
	big_enemy = load_image("data/gfx/invader3a.png");
	medium_enemy1 = load_image("data/gfx/invader2a.png");
	medium_enemy2 = load_image("data/gfx/invader2b.png");
	small_enemy1 = load_image("data/gfx/invader1a.png");
	small_enemy2 = load_image("data/gfx/invader1b.png");
	bulet_frame0 = load_image("data/gfx/bulet00.png");
	bulet_frame1 = load_image("data/gfx/bulet01.png");
	s_block00 = load_image("data/gfx/block00.png");
	s_block01 = load_image("data/gfx/block01.png");
	s_block02 = load_image("data/gfx/block02.png");
	s_block03 = load_image("data/gfx/block03.png");
	s_block04 = load_image("data/gfx/block04.png");
	s_block05 = load_image("data/gfx/block05.png");
	s_block06 = load_image("data/gfx/block06.png");
	s_block07 = load_image("data/gfx/block07.png");
	s_select1 = load_image("data/gfx/select1.png");
	SDL_SetAlpha(s_select1, SDL_SRCALPHA, 60);
	for ( int n = 0; n < 9; n++ )
	{
		stringstream m;
		m << "data/gfx/p1_locked" << n << ".png";
		s_p1power[n] = load_image(m.str());
	}

	s_blast[0] = load_image("data/gfx/blast0.png");
	s_blast[1] = load_image("data/gfx/blast1.png");
	s_blast[2] = load_image("data/gfx/blast2.png");
	s_blockbulet = load_image("data/gfx/blockbulet.png");
	SDL_SetAlpha(s_blockbulet, SDL_SRCALPHA, 120);
	s_nuke = load_image("data/gfx/nuke.png");
	s_menu = load_image("data/gfx/menu.png");
	s_attacker = load_image("data/gfx/attacker.png");
	s_attacker_shot = load_image("data/gfx/attacker_shot.png");
	s_select2 = load_image("data/gfx/select2.png");
	s_bigbulet = load_image("data/gfx/enemyammo.png");
	s_biglaser = load_image("data/gfx/biglaser.png");
	s_game_over = load_image("data/gfx/game_over.png");
	s_help = load_image("data/gfx/help.png");
	SDL_SetAlpha(s_select2, SDL_SRCALPHA, 60 );

	for ( int l = 0; l < 7; l++ )
	{
		stringstream g;
		g << "data/gfx/p2_power" << l << ".png";
		s_p2power[l] = load_image(g.str());
	}

	for ( int l = 0; l < 9; l++ )
	{
		stringstream o;
		o << "data/gfx/p1_locked" << l << ".png";
		s_p3power[l] = load_image(o.str());
	}

	s_locked = load_image("data/gfx/p1_locked0.png");

	f_score = TTF_OpenFont("data/font/SF Funk Master Oblique.ttf", 40);
	f_stats = TTF_OpenFont("data/font/SF Funk Master Oblique.ttf", 20);

	//Muzik
	m_menu = Mix_LoadMUS("data/sfx/menu.mid");
	m_song1 = Mix_LoadMUS("data/sfx/song1.mid");
	m_song2 = Mix_LoadMUS("data/sfx/song2.mid");
	m_song3 = Mix_LoadMUS("data/sfx/song3.mid");
	m_explode = Mix_LoadWAV("data/sfx/destroy.wav");

	if ( m_explode == NULL )
	{
		return false;
	}

	return true;
}

//Initilizacija
bool init()
{
	if ( SDL_Init(SDL_INIT_EVERYTHING) == -1 )
	{
		return false;
	}

	if ( TTF_Init() == -1 )
	{
		return false;
	}

	if ( Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 512) == -1 )
	{
		return false;
	}

	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_RESIZABLE | SDL_FULLSCREEN);

	if ( screen == NULL )
	{
		return false;
	}

	SDL_WM_SetCaption("Space Invaders Versus", NULL);

	return true;
}

//Kolizija èeken
bool check_collision(SDL_Rect A, SDL_Rect B)
{
	//The sides of the rectangles 
	int leftA, leftB; 
	int rightA, rightB; 
	int topA, topB; 
	int bottomA, bottomB; 

	//Calculate the sides of rect A 
	leftA = A.x; 
	rightA = A.x + A.w; 
	topA = A.y; 
	bottomA = A.y + A.h; 

	//Calculate the sides of rect B 
	leftB = B.x; 
	rightB = B.x + B.w; 
	topB = B.y; 
	bottomB = B.y + B.h; 

	//If any of the sides from A are outside of B 
	if( bottomA <= topB ) 
	{ 
		return false;
	} 
	
	if( topA >= bottomB ) 
	{ 
		return false; 
	} 
	
	if( rightA <= leftB ) 
	{ 
		return false; 
	} 
	
	if( leftA >= rightB ) 
	{ 
		return false; 
	} 
	
	//If none of the sides from A are outside B 
	return true; 
}

//Pucanje
void clean_up()
{
	SDL_FreeSurface(background);
	SDL_FreeSurface(player1);
	SDL_FreeSurface(player1_shadow);
	SDL_FreeSurface(big_enemy);
	SDL_FreeSurface(medium_enemy1);
	SDL_FreeSurface(medium_enemy2);
	SDL_FreeSurface(small_enemy1);
	SDL_FreeSurface(small_enemy2);
	SDL_FreeSurface(bulet_frame0);
	SDL_FreeSurface(bulet_frame1);
	SDL_FreeSurface(s_block00);
	SDL_FreeSurface(s_block01);
	SDL_FreeSurface(s_block02);
	SDL_FreeSurface(s_block03);
	SDL_FreeSurface(s_block04);
	SDL_FreeSurface(s_block05);
	SDL_FreeSurface(s_block06);
	SDL_FreeSurface(s_block07);

	TTF_CloseFont(f_score);

	//Muzika
	Mix_FreeMusic(m_menu);
	Mix_FreeMusic(m_song1);
	Mix_FreeMusic(m_song2);
	Mix_FreeMusic(m_song3);
	Mix_FreeChunk(m_explode);

	o_level.save_level();

	Mix_CloseAudio();

	TTF_Quit();

	SDL_Quit();
}
