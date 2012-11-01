#ifndef OBJECTS_H
#define OBJECTS_H

#include <string>
#include <vector>
#include "Classes.h"

using namespace std;

//Premikanje nas.
extern Timer enemyMovement;

//Player 1
extern Player1 player_1;
extern Player1 player_2;
extern Attacker o_player2_attacker;

extern Score o_player1_score;
extern Score o_player2_score;

extern Buy_Sys_Play1 o_player1_buy;
extern Buy_Sys_Play1 o_player2_buy;
extern Buy_System_Attacker o_player3_buy;

extern Level o_level;

extern Blocks blocks;

//Kontrola sovražnikov
extern EnemyControl enemycontrol;

//Fps
extern Timer FPS;

extern Timer delta;

#endif