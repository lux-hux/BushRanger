#ifndef sdl2_testing_main_h
#define sdl2_testing_main_h

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>


#define PLAYER_MOVEMENT_SPEED 7
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 640
#define ENEMY_HEIGHT 48
#define ENEMY_WIDTH 48
#define PLAYER_HEIGHT 48
#define PLAYER_WIDTH 48


typedef struct Bullet{

    float x; 
    float y;
    float dx;
    float dy;
    float angle;

    struct Bullet* next; 
    struct Bullet* prev;

}Bullet; 

typedef struct Player{

    float x;
    float y;

    float firing;
    float reloading;
    float x_aim;
    float y_aim;
    float bullet_angle;

    float moving;
    float face_left;
    float face_right;

    float alive;

    int animFrame;

    struct Player* enemy_next; 
    struct Player* enemy_prev; 

}Player;


typedef struct{

    SDL_Renderer *renderer;
    SDL_Window *window; 

    float left;
    float right;
    float up;
    float down;
    float fire;

    int time;

    Bullet* start_bullet; 
    Bullet* end_bullet;

    Bullet* start_bullet_enemy;
    Bullet* end_bullet_enemy;

    SDL_Texture *texture_player[12];
    SDL_Texture *texture_enemy[5];

    SDL_Texture *background;

    SDL_Texture *bullet_texture;

    Player* start_enemy;
    Player* end_enemy;

    int x; 
    int y;

    SDL_Rect camera; 

} Application; 

// Prototypes

int random_int(int min, int max); 

void initSDL(Application *app);

void prepareScene(Application *app);

void presentScene(Application *app);

SDL_Texture *loadTexture(Application *app,char* fileName);

void deleteBullets(Bullet *bullet_1st, Bullet *bullet_2nd, Bullet **bullet_last);

void fireBullet(Application *app, Player *player);

void fireBulletEnemy(Application *app, Player *enemy);

#endif
