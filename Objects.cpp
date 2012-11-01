#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "Classes.h"
#include "Objects.h"

using namespace std;

//Objekti
//Igralec 1

Player1 player_1;
Player1 player_2;
Attacker o_player2_attacker;

Score o_player1_score;
Score o_player2_score;

Buy_Sys_Play1 o_player1_buy;
Buy_Sys_Play1 o_player2_buy;
Buy_System_Attacker o_player3_buy;

Blocks blocks;

Level o_level;

//Kontrola sovražnikov
EnemyControl enemycontrol;

//Premikanje ene
Timer enemyMovement;

//Fps
Timer FPS;

Timer delta;
