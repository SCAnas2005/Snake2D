
#ifndef __MAIN__C__
    #define __MAIN__C__
    #include "globals.h"
#include "enums.h"

    #define TRUE 1
    #define FALSE 0

    SDL_Window *window = NULL; // fenêtre
    SDL_Renderer *render = NULL; // Rendu

    SDL_Rect area[AREA_S][AREA_S]; // Area avec réctangle
    char areaSTR[AREA_S][AREA_S]; // Area avec str

    Directions direction = DIR_None;

    ScreenState state = Loading;

    SDL_Surface *bg; // Surface du background quand etat == 0
    SDL_Texture *texture_bg; // Texture du background (etat == 0)

    SDL_Surface *title; // Surface du titre (etat == 0)
    SDL_Texture *texture_title; // Texture titre (etat == 0)

    SDL_Surface *button; // Surface pour le boutton
    SDL_Texture *texture_button; // Surface pour la texture


    

    SDL_Rect rect = {50, 250, 200, 150};
    
#endif