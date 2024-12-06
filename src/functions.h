
#ifndef __FUNCTIONS__C__
    #define __FUNCTIONS__C__

    #include "globals.h"

    void setError(char *message); // Erreur
    void destroy(SDL_Window *window, SDL_Renderer *render, SDL_Texture *t1, SDL_Texture *t2, SDL_Texture *t3);


    void createArea(SDL_Rect area[][AREA_S]);
    void clearScreen(SDL_Renderer *render);
    void drawBackround(SDL_Renderer *render, SDL_Rect area[20][20]); // Affiche la map


    void fps60(int start); // Fonctions pour limiter le nombre d'image par seconde à 60

    void drawBackgroundState0(SDL_Renderer *render, SDL_Texture *texture); // Dessine le background quand state == 0
    void drawTitle(SDL_Renderer *render, SDL_Texture *texture); // Dessine le titre quand state == 0
    void drawButtonPlay(SDL_Renderer *render, SDL_Texture *texture, SDL_Rect rect); // Dessine le boutton etat == 0
    int checkPlayButton(int Xmouse, int Ymouse, SDL_Rect button);

#endif