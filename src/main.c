
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "variables.h" // Variables
#include "functions.h" // Fonctions utiles
#include "snake.h" // Fonctions pour le serpent
#include "apple.h" // Fonctions pour la pomme


Apple apple;
Snake snake;

TTF_Font *font;

int Exit()
{
    TTF_CloseFont(font); // Ferme le fichier de la police
    SDL_FreeSurface(apple.image); // Libération de la surface
    destroy(window, render, texture_bg, texture_title, texture_button); // Libération des ressources
    TTF_Quit(); // Libération module font.
    SDL_Quit(); // Libération des modules SDL
    exit(0);
}

void init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) setError("init"); // Initialisation SDL
    if (TTF_Init() != 0) setError("ttf_init"); // Initialisation font

    window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, 0); // Creation fenêtre
    if (window == NULL) setError("window == NULL");

    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE); // Création rendu
    if (render == NULL) {destroy(window, NULL, NULL, NULL, NULL); setError("render == NULL");}

    createArea(area); // Creating the rect area

    bg = IMG_Load(ASSET_FOLDER"bg.jpg"); // Chargement image background
    texture_bg = SDL_CreateTextureFromSurface(render, bg); // Création texture background
    SDL_FreeSurface(bg);


    font = TTF_OpenFont("C:/Windows/Fonts/Arial.ttf", 50); // Police du titre

    SDL_Color title_color = {255,20,20,255};
    title = TTF_RenderText_Blended(font, "SNAKE", title_color);
    texture_title = SDL_CreateTextureFromSurface(render, title);
    SDL_FreeSurface(title); // Surface mémoire libéré
    
    SDL_Rect rect = {50, 250, 200, 150};
    button = IMG_Load(ASSET_FOLDER"playButton.png");
    if (button == NULL) { setError("erreur button image"); }
    texture_button = SDL_CreateTextureFromSurface(render, button);
    SDL_FreeSurface(button); // Mémoire libéré

    snake = initSnake(); // initialisation de la structure snake
    apple = initApple(); // initialisation de la structure apple
}




void update()
{
    Uint32 start = SDL_GetTicks(); // Temps départ

    SDL_Event event;
    while (SDL_PollEvent(&event)) // Attente d'evenement
    {
        switch (event.type)
        {
            case SDL_QUIT:
                Exit();
                break;
            
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_UP:
                        direction = DIR_Up;
                        break;
                    case SDLK_DOWN:
                        direction = DIR_Down;
                        break;
                    case SDLK_LEFT:
                        direction = DIR_Left;
                        break;
                    case SDLK_RIGHT:
                        direction = DIR_Right;
                        break;
                    
                    default:
                        break;
                }
                break;
            
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT && state == Loading)
                {
                    if (checkPlayButton(event.button.x, event.button.y, rect))
                    {
                        state = Gameplay; // Passe au jeu
                        snake = initSnake(); // initialisation de la structure snake
                        apple = initApple(); // initialisation de la structure apple
                    }
                }
                break;

            default:
                break;
        }
    }

    if (state == Gameplay)
    {
        // Collisions
        if (snakeCollision(snake)) // Detection colisions avec corps et mur
        {
            printf("You lose !!\n");
            Exit();
        }
        if (snakeAppleColision(snake, apple)) // Detection colisions avec pommes
        {
            addBodySnake(&snake); // Ajout d'un corps
            updateApple(&apple); // Mis à jour de la pomme
        }

        // Espace update
        updateSnakeHead(&snake, direction); // Met à jour le serpent
    }

    fps60(start); // fonctions pour mettre 60 images par secondes
}

void draw(SDL_Renderer *renderer)
{
    if (state == Loading)
    {
        drawBackgroundState0(renderer, texture_bg);
        drawTitle(renderer, texture_title);
        drawButtonPlay(renderer, texture_button, rect);
    }
    else if (state == Gameplay)
    {
        clearScreen(renderer); // Efface l'écran
        drawBackround(renderer, area); // Dessine background
        drawSnakeHead(renderer, snake, area); // dessine tête du serpent
        drawApple(renderer, apple, area); // Dessine la pomme
    }

    SDL_RenderPresent(render); // Actualise l'écran
}



int main(int argv, char **argc)
{
    init();
    while (TRUE)
    {
        // Update
        update();
        // Draw
        draw(render);
    }


    Exit();
    return EXIT_SUCCESS;
}