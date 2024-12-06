
#ifndef __APPLE__C__
#define __APPLE__C__

#include <SDL.h>

typedef struct Coordonate
{
    int L;
    int C;
} Coord;

typedef struct Apple
{
    SDL_Surface *image;
    Coord pos;
    int isShow;

} Apple;

Apple initApple(void); // Initialisation de la pomme
void drawApple(SDL_Renderer *render, Apple apple, SDL_Rect area[20][20]); // Affichage de la pomme
void updateApple(Apple *apple);

#endif
