
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL.h>
#include <SDL_image.h>
#include "apple.h"
#include "globals.h"


// Fonctions pour faire apparaître la pomme.

Apple initApple(void)
{
    SDL_Surface *image = IMG_Load(ASSET_FOLDER"apple.png");
    Coord pos = {15,2};
    Apple apple = {image, pos, 0};
    return apple;
}

void drawApple(SDL_Renderer *render, Apple apple, SDL_Rect area[20][20])
{
    SDL_Texture *texture = SDL_CreateTextureFromSurface(render, apple.image);
    SDL_RenderCopy(render, texture, NULL, &area[apple.pos.L][apple.pos.C]);

    SDL_DestroyTexture(texture);
}

void updateApple(Apple *apple)
{
    srand(time(NULL));

    int ligne = (rand() % 17)+1;
    int col = (rand() % 17) +1;

    apple->pos.L = ligne;
    apple->pos.C = col;
}