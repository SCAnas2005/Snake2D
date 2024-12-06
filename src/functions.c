
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_ttf.h>

#include "functions.h"
#include "globals.h"

void setError(char *message) // Mettre des erreurs
{
    SDL_Log("Error : %s > %s\n", message, SDL_GetError());
    TTF_Quit();
    SDL_Quit();
    exit(0);
}

void destroy(SDL_Window *window, SDL_Renderer *render, SDL_Texture *t1, SDL_Texture *t2, SDL_Texture *t3) // Libère les ressources
{
    if (t1 != NULL) SDL_DestroyTexture(t1);
    if (t2 != NULL) SDL_DestroyTexture(t2);
    if (t3 != NULL) SDL_DestroyTexture(t3);
    if (render != NULL) SDL_DestroyRenderer(render);
    if (window != NULL) SDL_DestroyWindow(window);
}

void createArea(SDL_Rect area[][AREA_S]) // Crée le tableau de rect
{
    for (int l = 0; l < AREA_S; l++) // Création de la map de rect
    {
        for (int c = 0; c < AREA_S; c++)
        {
            SDL_Rect rect = {c*25, l*25, 25, 25};
            area[l][c] = rect;
        }
    }
}

void drawBackround(SDL_Renderer *render, SDL_Rect area[20][20])
{
    SDL_SetRenderDrawColor(render, 255,255,255,255);

    for (int l = 0; l < 25; l++)
    {
        for (int c = 0; c < 25; c++)
        {
            SDL_RenderDrawRect(render, &area[l][c]);
        }
    }
}

void clearScreen(SDL_Renderer *render)
{
    SDL_SetRenderDrawColor(render, 0,0,0,255);
    SDL_RenderClear(render);
}

void fps60(int start)
{
    if (1000/60 > (SDL_GetTicks() - start))
    {
        SDL_Delay(1000/60 - (SDL_GetTicks() - start));
    }
}

/// ===================================================================================================

void drawBackgroundState0(SDL_Renderer *render, SDL_Texture *texture)
{
    SDL_Rect rect = {0, 0, 500, 500};
    SDL_RenderCopy(render, texture, NULL, &rect);
}

void drawTitle(SDL_Renderer *render, SDL_Texture *texture)
{
    SDL_Rect rect = {150, 50, 200, 30};
    SDL_RenderCopy(render, texture, NULL, &rect);
}

void drawButtonPlay(SDL_Renderer *render, SDL_Texture *texture, SDL_Rect rect)
{
    SDL_RenderCopy(render, texture, NULL, &rect);
}

int checkPlayButton(int Xmouse, int Ymouse, SDL_Rect button)
{
    if ( (Xmouse >= button.x && Xmouse <= (button.x+button.w)) && (Ymouse >= button.y && Ymouse <= (button.y+button.h)) )
        return 1;

    return 0; 
}