
#ifndef __SNAKE__C__
#define __SNAKE__C__

#include <SDL.h>
#include "apple.h"

typedef struct SnakeBody
{
    Coord bodyPos;

    SDL_Color color;
    int isValid;
} SnakeBody;

typedef struct Snake
{
    Coord headPos;
    int bodiesNumber;
    SnakeBody bodiesPos[100];
    int FRAME_PER_SECOND;
} Snake;

Snake initSnake(void); // Initialise un serpent

void drawBodySnake(SDL_Renderer *render, Snake snake, SDL_Rect area[20][20]); // Dessine le corps
void drawSnakeHead(SDL_Renderer *render, Snake snake, SDL_Rect area[20][20]); // Dessine le serpent

void updateSnakeHead(Snake *snake, char command); // permet le déplacement du serpent

void addBodySnake(Snake *snake, char command); // Ajout d'un corps du serpent

int snakeCollision(Snake snake); // Detection colision snake corps
int snakeAppleColision(Snake snake, Apple apple); // Detection collision snake pomme.


#endif