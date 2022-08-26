#include "main.h"

void deleteBullets(Bullet *bullet_1st, Bullet *bullet_2nd, Bullet *bullet_last)
{
        Bullet* prev_in_iter; 
        Bullet* curr_bullet;
        Bullet* bullet_last_ye;

        prev_in_iter = bullet_1st; 

        bullet_last_ye = bullet_last;

            for(curr_bullet = bullet_2nd; curr_bullet != NULL; curr_bullet = curr_bullet->next){

                if(curr_bullet->y >= 3500 || curr_bullet->y <= -3500 || curr_bullet->x >= 3500 || curr_bullet->x <= -3500){   

                    if (curr_bullet -> next == NULL){

                        curr_bullet -> prev -> next = NULL; 
                        bullet_last_ye = curr_bullet->prev; 

                    } else {

                        curr_bullet->next->prev = curr_bullet->prev; 
                        curr_bullet->prev->next = curr_bullet->next; 

                    }

                free(curr_bullet);

                curr_bullet = prev_in_iter; 
                }

            prev_in_iter = curr_bullet; 

            }

}

void fireBullet(Application *app, Player *player)
{

    player->reloading = 15; 

    Bullet* new_bullet = malloc(sizeof(Bullet));

    if (new_bullet == NULL){
        printf("Insufficient memory to allocate for bullet \n");
        exit(1);
    }

    new_bullet->x = player->x + (PLAYER_WIDTH/2);
    new_bullet->y = player->y;
    new_bullet->next = NULL;

    new_bullet->dx = 0; 
    new_bullet->dy = 0;
    new_bullet->angle = 0;


    // The new bullet is preceded by the previous end bullet 

    new_bullet->prev = app->end_bullet;

    // The previous end bullet in the list is now followed by the new bullet

    app->end_bullet->next = new_bullet; 

    // The new end bullet is the new bullet

    app->end_bullet = new_bullet; 
    
}

void fireBulletEnemy(Application *app, Player *enemy)
{

    enemy->reloading = 50; 

    Bullet* new_bullet_enemy = malloc(sizeof(Bullet));

    if (new_bullet_enemy == NULL){
        printf("Insufficient memory to allocate for bullet \n");
        exit(1);
    }

    new_bullet_enemy->x = enemy->x + ENEMY_WIDTH/2;
    new_bullet_enemy->y = enemy->y + ENEMY_HEIGHT/2;
    new_bullet_enemy->dx = enemy->x_aim;

    new_bullet_enemy->dy = enemy->y_aim;
    new_bullet_enemy->angle = enemy->bullet_angle;
    new_bullet_enemy->next = NULL;


    // The new bullet is preceded by the previous end bullet 
    new_bullet_enemy->prev = app->end_bullet_enemy;

    // The previous end bullet in the list is now followed by the new bullet

    app->end_bullet_enemy->next = new_bullet_enemy; 

    // The new end bullet is the new bullet

    app->end_bullet_enemy = new_bullet_enemy; 

}