#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "Globals.h"
#include "Functions.h"

using namespace std;

SDL_Surface * load_image ( string filename );

void apply_surface ( int x, int y, SDL_Surface * src, SDL_Surface * dst, SDL_Rect * clip);

bool init();

bool check_collision(SDL_Rect A, SDL_Rect B);

bool load_files();

void create_objects();

void clean_up();

#endif