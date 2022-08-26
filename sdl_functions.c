#include "main.h"


int random_int(int min, int max)
{
   return min + rand() % (max - min);
}

void initSDL(Application *app)
{

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Failed to initialise SDL: %s \n", SDL_GetError());
        exit(1);
    }

    app->window = SDL_CreateWindow("Game Window", \
    SDL_WINDOWPOS_UNDEFINED, \
    SDL_WINDOWPOS_UNDEFINED, \
    //the width of the window, in screen coordinates
    640, \
    //the height of the window, in screen coordinates 
    480, \
    // 0, or one or more SDL_WindowFlags OR'd together
    // used for things like resizable window, full-screen etc.
    0);

    if(!app->window)
    {
        printf("Failed to open %d x %d window: %s \n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    
    app->renderer = SDL_CreateRenderer(app->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(!app->renderer)
    {
        printf("Failed to create renderer: %s \n", SDL_GetError());
        exit(1);
    }

}

void prepareScene(Application *app)
{
    SDL_SetRenderDrawColor(app->renderer, 0, 0, 255, 255);
    SDL_RenderClear(app->renderer);

}

void presentScene(Application *app)
{
    SDL_RenderPresent(app->renderer);

}


SDL_Texture *loadTexture(Application *app,char* fileName)
{

    SDL_Texture *texture;

    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", fileName);

    texture = IMG_LoadTexture(app->renderer, fileName);  

    if(texture ==NULL){
        printf("Cannot find texture %s \n", fileName);
         SDL_Quit();
         exit(1);
    }

    return texture;
}