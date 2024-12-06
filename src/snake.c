
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

#include "snake.h"

// Fonctions du serpent

Snake initSnake(void)
{
    Coord headPos = {10,10}; // Position de la tête
    Snake snake; // Serpent 
    snake.headPos = headPos; // Position
    snake.bodiesNumber = 0; // Nombe de serpent derrière lui
    snake.FRAME_PER_SECOND = 5; // Frame par seconde (vitesse)

    SDL_Color color = {255,255,255,255}; // Couleur du corps du serpent
    SnakeBody body = {snake.headPos, color, 0}; // Corps du serpent
    for (int i = 0; i < 100; i++)
    {
        snake.bodiesPos[i] = body;
    }

    return snake;
}

void drawBodySnake(SDL_Renderer *render, Snake snake, SDL_Rect area[20][20]
)
{
    SDL_Rect rect;
    SDL_SetRenderDrawColor(render, 0,251,0,255);
    for (int i = 0; i < snake.bodiesNumber; i++)
    {
        rect = area[snake.bodiesPos[i].bodyPos.L][snake.bodiesPos[i].bodyPos.C];
        rect.w -= 4; // Diminutions 
        rect.h -= 4; // Des
        rect.x += 2; // Cases
        rect.y += 2; // .
        if (snake.bodiesPos[i].isValid)
            SDL_RenderFillRect(render, &rect);
    }
}

void drawSnakeHead(SDL_Renderer *render, Snake snake, SDL_Rect area[20][20])
{
    SDL_SetRenderDrawColor(render, 0,163,0, 255);

    SDL_RenderFillRect(render, &area[snake.headPos.L][snake.headPos.C]);
    drawBodySnake(render, snake, area);
}

void updateSnakeHead(Snake *snake, char command)
{
    int line, col;
    switch (command)
    {
        case 'u':
            line = -1;
            col = 0;
            break;
        case 'd':
            line = 1;
            col = 0;
            break;
        case 'l':
            col = -1;
            line = 0;
            break;
        case 'r':
            col = 1;
            line = 0;
            break;
        default:
            break;
    }

    if ((snake->headPos.L+line >= 0 && snake->headPos.L+line < 20) && (snake->headPos.C+col >= 0 && snake->headPos.C+col < 20))
    {
        if (snake->FRAME_PER_SECOND <= 0)
        {
            int i = snake->bodiesNumber - 1;
            while (i > 0)
            {   
                snake->bodiesPos[i].bodyPos = snake->bodiesPos[i-1].bodyPos;
                i--;
            }

            snake->bodiesPos[0].bodyPos = snake->headPos;

            (snake->headPos.L) += line;
            (snake->headPos.C) += col;

            snake->FRAME_PER_SECOND = 5;
        }
        else {(snake->FRAME_PER_SECOND)--;}
        
    }
}

void addBodySnake(Snake *snake, char command)
{
    if (snake->bodiesNumber == 0)
    {
        snake->bodiesPos[0].bodyPos.C = snake->headPos.C;
        snake->bodiesPos[0].bodyPos.L = snake->headPos.L + 1;
        snake->bodiesPos[0].isValid = 1;
    }

    snake->bodiesPos[snake->bodiesNumber].bodyPos.C = snake->bodiesPos[snake->bodiesNumber - 1].bodyPos.C;
    snake->bodiesPos[snake->bodiesNumber].bodyPos.L = snake->bodiesPos[snake->bodiesNumber - 1].bodyPos.L;
    snake->bodiesPos[snake->bodiesNumber].isValid = 1;


    (snake->bodiesNumber) += 1;
}

int snakeCollision(Snake snake)
{
    Coord head = snake.headPos;
    
    if ( (head.C == 0) || (head.L == 0) || (head.C == 19) || (head.L == 19) ) return 1; 
    
    for (int i = 0; i < snake.bodiesNumber; i++)
    {
        if ( (head.C == snake.bodiesPos[i].bodyPos.C) && (head.L == snake.bodiesPos[i].bodyPos.L) ) return 1;
    }

    return 0;
}

int snakeAppleColision(Snake snake, Apple apple)
{
    if ( (snake.headPos.C == apple.pos.C) && (snake.headPos.L == apple.pos.L) ) return 1;

    return 0;
}