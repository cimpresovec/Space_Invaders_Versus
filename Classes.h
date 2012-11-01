#ifndef CLASSES_H
#define CLASSES_H

#include <string>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "Globals.h"
#include "Functions.h"
#include "Classes.h"

using namespace std;

//Timer
class Timer
{
public:

	//Timer
	int ticks;

	//Initi
	Timer();

	//Start
	void start();

	void restart();

	//Return
	int get_ticks();
};

//Particle exploda
class Explode_Particle
{
private:
	SDL_Rect box;

	float i_x;
	float i_y;

	float i_xvel;
	float i_yvel;
	int i_speed;

	int i_frame;

	


public:

	Explode_Particle();

	bool b_alive;

	int i_player;
	int i_a;

	void set_up();

	void create( int x, int y );

	void move(int delta);

	void check_enemy();

	bool alive();

	void show();
};



//Metek
class Bulet
{
public:

	float x;
	float y;

	float yVel;

	SDL_Rect box;

	bool b_laser;

	bool alive;

	int frame;

	SDL_Surface * bulet_surface;

	//Initilizacija
	Bulet();

	void create(int X, int Y);

	void show();

	void animate();

	void move( Uint32 delta );
};

//Senca...
class Shadow
{
public:

	int x;
	int y;

	bool alive;

	int frame;

	SDL_Surface * type;

	//intili
	Shadow( int X, int Y, SDL_Surface * TYPE );

	//Naštimanje
	void set_up( int X, int Y, SDL_Surface* TYPE );

	//show
	void show();

	//briši
	bool dead();
};

class Level
{
	

public:

	int i_level;

	Level();

	void get_level( int yes );

	void save_level();

	int i_high_level;

	void render_level();


	void show();

	void set_difficulity();
};

class Bomb
{
private:

	int i_x;
	float i_y;

	float i_yvel;

	int i_frame;

	int i_time;

		

public:

	Bomb(int part );

	SDL_Rect box;

	int i_player;

	int i_a;

	bool b_alive;
 
	bool b_explode;

	int i_particles;

	vector<Explode_Particle> o_particle;

	void create( int x, int y, int speed);

	void button();

	void move( int delta );

	bool alive();

	void explode();

	void show();
};

class Block
{
private:

	int state;

	bool b_shot;

	SDL_Surface * type;

public:

	Bulet* o_bulet;

	SDL_Rect box;

	bool alive;

	Block();

	void create(int x, int y);

	void change_state();

	void allow_shot();

	void do_logic(Uint32 delta);

	void shot();

	void check_bulet();

	void heal();

	void show();
};

class Buy_Sys_Play1
{
private:
	int i_state;

	int i_x;
	int i_y;

	bool b_move;
	bool b_buy;

	

public:

	bool b_unlocked[7];

	int i_player;

	void set_up();

	Buy_Sys_Play1();
	 
	void handle_input();

	void buy();
	void buy2();

	void reset();

	void explode();

	void move();

	void unlock();

	void show();
};

class Buy_System_Attacker
{
private:

	int i_state;
	int i_x;
	int i_y;

	bool b_move;
	bool b_buy;

public:

	Buy_System_Attacker();

	void handle_input();
	
	void buy();

	void move();

	void show();
};

//Igralec
class Player1
{
private:

	//Senca
	int s;
	int se;

	//Koordinate
	float x;
	float y;

	//Hitrost
	float xVel;
	float yVel;

	int i_shottime;

	bool shoting;

	bool b_blast;

	
	
	//Sence
	vector<Shadow> player1_Shadow;

public:

	//Koordinate škatle
	SDL_Rect box;

	int i_player;

	bool b_fast;

	int i_lives;
	void set_up();

	bool b_blastagain;

	bool b_super;

	bool b_nuke;

	vector<Bomb> o_blast;
	Bomb * o_nuke;

	vector<Bulet> player1_bulet;
	vector<Bulet> player1_laser;

	//premikanje
	bool moving;

	void check_time();

	void add_time(int time);

	void set_lives(int set);
	int get_lives();

	void set_time(int time);

	int i_blastammo;

	void clean_up();

	int i_buletn;

	Player1();

	//Input
	void hande_input();

	//Strelaje
	void shot();

	void blast();

	void show_stats();

	//Premik
	void move(Uint32 delta);

	//Prikaz
	void show();

	//Prikaz in delo z sencami
	void show_shadow();

	void show_bulet();
};

//Sovražniki
class Enemy
{
public:

	//X in Y
	int x, y;

	bool b_moving;

	int i_myY;

	//Škatla
	SDL_Rect box;

	//Èe je nareto
	bool created;

	//Èe je živo
	bool alive;

	int frame;

	//Slika
	SDL_Surface * type;

	Enemy();

	//Naštimannje
	void set_up( int X, int Y, SDL_Surface * TYPE );

	//Premikanje
	void move();

	bool check_bulet();
	bool check_bulet2();

	//prikaz
	void show();

	void make_me();

	//Animacija
	void animate( int enemy );
};

//Kontrola sovražnikov
class EnemyControl
{
private:
	
	//x in y sovražnikov
	int X, Y;

	int e1;
	int e2;
	int e3;

	int i_sound;

	int i_bulet;

	int direction;

	int pre_direction;

public:

	
	bool b_ammo;

	//Sovražniki
	vector<Enemy> smallEnemy;
	vector<Enemy> mediumEnemy;
	vector<Enemy> bigEnemy;
	vector<Bulet> o_bulet;

	int speed;

	int acceleration;

	//Izdelava sovražnikov
	EnemyControl();

	void check_collisions();

	void make_ammo();
	//ko mora
	void do_logic( int time );

	void create_enemys();

	//Strelaje sovražnikov
	void enemy_shot();

	void create_bulet( SDL_Rect place );

	void check_bulet_player();

	bool sacrifice();

	//Animacija sovražnikov
	void animate_enemy();

	//Premikanj sovražnikov
	void move_enemy();

	bool check_down();

	bool make_new();

	bool check_dead();

	//Prikaz sovražnikov
	void show_enemy();

};

//Player 2 attacker
class Attacker
{
private:
	
	float i_x;
	float i_y;

	SDL_Rect box;

	float i_xVel;
	int i_speed;

	bool b_laser;

	bool b_shot;

	int i_time;

public:

	vector<Bulet> o_bulet;

	Attacker();

	void handle_input();
	void move(Uint32 delta);
	void show();
	bool get_laser();
	void check_player();
	void laser();
	void shot();
	void add_time(int x);
	void show_stats();
};

//Toèke
class Score
{
private:

	int i_score;
	int i_x;
	int i_y;
	int i_time;
	int i_timer_score;

public:
	int i_addscore;

	Score();
	void set_up( int X, int Y );
	void show_score( int player );
	void render_score( int player );
	void add_score(int addition);
	void set_score();
	void change_score(int set);
	int get_score();
	void raise_score(int pl);
	void score_logic();
};



class Blocks
{
public:

	bool b_shot;

	Blocks();

	vector<Block> o_Block;

	void create_blocks();

	void check_bulets();

	void shot();

	void do_logic(Uint32 delta);
	void show_blocks();
};

#endif