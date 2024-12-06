
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "variables.h" // Variables
#include "functions.h" // Fonctions utiles
#include "snake.h" // Fonctions pour le serpent
#include "apple.h" // Fonctions pour la pomme

int main(int argv, char **argc)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) setError("init"); // Initialisation SDL
    if (TTF_Init() != 0) setError("ttf_init"); // Initialisation font

    // ==================================================================================================   
    window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, 0); // Creation fenêtre
    if (window == NULL) setError("window == NULL");

    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE); // Création rendu
    if (render == NULL) {destroy(window, NULL, NULL, NULL, NULL); setError("render == NULL");}
    // ==================================================================================================
    createArea(area); // Creating the rect area

    bg = IMG_Load(ASSET_FOLDER"bg.jpg"); // Chargement image background
    texture_bg = SDL_CreateTextureFromSurface(render, bg); // Création texture background
    SDL_FreeSurface(bg);

    TTF_Font *font = TTF_OpenFont("C:/Windows/Fonts/Arial.ttf", 50); // Police du titre

    SDL_Color title_color = {255,20,20,255};
    title = TTF_RenderText_Blended(font, "SNAKE", title_color);
    texture_title = SDL_CreateTextureFromSurface(render, title);
    SDL_FreeSurface(title); // Surface mémoire libéré
    
    SDL_Rect rect = {50, 250, 200, 150};
    button = IMG_Load(ASSET_FOLDER"playButton.png");
    if (button == NULL) { setError("erreur button image"); }
    texture_button = SDL_CreateTextureFromSurface(render, button);
    SDL_FreeSurface(button); // Mémoire libéré

    Snake snake = initSnake(); // initialisation de la structure snake
    Apple apple = initApple(); // initialisation de la structure apple


    SDL_bool started = SDL_TRUE; // commence ou pas
    while (started)
    {
        Uint32 start = SDL_GetTicks(); // Temps départ
        SDL_Event event;
        while (SDL_PollEvent(&event)) // Attente d'evenement
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    started = SDL_FALSE;
                    break;
                
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_UP:
                            command = 'u';
                            break;
                        case SDLK_DOWN:
                            command = 'd';
                            break;
                        case SDLK_LEFT:
                            command = 'l';
                            break;
                        case SDLK_RIGHT:
                            command = 'r';
                            break;
                        
                        default:
                            break;
                    }
                    break;
                
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT && state == 0)
                    {
                        if (checkPlayButton(event.button.x, event.button.y, rect))
                        {
                            state = 1; // Passe au jeu
                            Snake snake = initSnake(); // initialisation de la structure snake
                            Apple apple = initApple(); // initialisation de la structure apple
                        }
                    }
                    break;

                default:
                    break;
            }
        }
        
        if (state == 0)
        {
            drawBackgroundState0(render, texture_bg);
            drawTitle(render, texture_title);
            drawButtonPlay(render, texture_button, rect);
        }
        else if (state == 1) // Etat de l'écran == 1 (JEU)
        {
            // Espace dessin 
            clearScreen(render); // Efface l'écran
            drawBackround(render, area); // Dessine background
            drawSnakeHead(render, snake, area); // dessine tête du serpent
            drawApple(render, apple, area); // Dessine la pomme

            // Collisions
            if (snakeCollision(snake)) // Detection colisions avec corps et mur
            {
                printf("You lose !!\n");
                //state = 0; // Reviens à l'acceuil
                started = SDL_FALSE;
            }
            if (snakeAppleColision(snake, apple)) // Detection colisions avec pommes
            {
                addBodySnake(&snake, command); // Ajout d'un corps
                updateApple(&apple); // Mis à jour de la pomme
            }

            // Espace update
            updateSnakeHead(&snake, command); // Met à jour le serpent
        }

        // Actualisation
        SDL_RenderPresent(render); // Actualise l'écran
        fps60(start); // fonctions pour mettre 60 images par secondes
    }


    TTF_CloseFont(font); // Ferme le fichier de la police
    SDL_FreeSurface(apple.image); // Libération de la surface
    destroy(window, render, texture_bg, texture_title, texture_button); // Libération des ressources
    TTF_Quit(); // Libération module font.
    SDL_Quit(); // Libération des modules SDL
    return EXIT_SUCCESS;
}