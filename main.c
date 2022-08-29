#include "main.h"


void collisionDetect(Application *app, Player *player){

        // Dimensions of the man in width (mw) and height (mh)
        float mw = PLAYER_WIDTH;
        float mh = PLAYER_HEIGHT;
        // Assigns location of the man (man.x) and (man.y) to mx and my variables for the sake of conciseness and brevity
        float mx= player->x;
        float my= player->y;

        float bx;
        float by;
        float bw;
        float bh; 

        for(Bullet* iter_bullet_enemy  = app->start_bullet_enemy->next; iter_bullet_enemy != NULL; iter_bullet_enemy = iter_bullet_enemy->next){
       
//Iterate through every bullet and assign the values to bx, by, bw, bh
        float bx = iter_bullet_enemy->x;
        float by = iter_bullet_enemy->y;
        float bw = 8;
        float bh = 8; 

// Check if the bullet is within the bounds of the player

            if(bx + bw < mx + mw && bx > mx)
            {
                if(by + bh < my + mh && by > my){
                    player->alive = 1;
                }
            }

        }

        float mw_enemy = ENEMY_WIDTH;
        float mh_enemy = ENEMY_HEIGHT;

        for(Bullet* iter_bullet  = app->start_bullet->next; iter_bullet != NULL; iter_bullet = iter_bullet->next){
            
            for(Player* iter_player  = app->start_enemy->enemy_next; iter_player != NULL; iter_player = iter_player->enemy_next){
                
                float mx_enemy= iter_player->x;
                float my_enemy= iter_player->y;

                float bx = iter_bullet->x;
                float by = iter_bullet->y;
                float bw = 8;
                float bh = 8; 
                if(bx + bw < mx_enemy + mw_enemy && bx > mx_enemy){
                    if(by + bh < my_enemy + mh_enemy && by > my_enemy){
                        iter_player->alive = 1;
                    }
                }

            }

        }

    }



void doKeyDown(SDL_KeyboardEvent *event, Application *app)
{
	if (event->repeat == 0)
	{
		if (event->keysym.scancode == SDL_SCANCODE_UP)
		{
			app->up = 1;
		}

		if (event->keysym.scancode == SDL_SCANCODE_DOWN)
		{
			app->down = 1;
		}

		if (event->keysym.scancode == SDL_SCANCODE_LEFT)
		{
			app->left = 1;
		}

		if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
		{
			app->right = 1;
		}

        if (event->keysym.scancode == SDL_SCANCODE_SPACE)
        {
	        app->fire = 1;
        }

	}
}


void doKeyUp(SDL_KeyboardEvent *event, Application *app)
{
	if (event->repeat == 0)
	{
		if (event->keysym.scancode == SDL_SCANCODE_UP)
		{
			app->up = 0;
            
		}

		if (event->keysym.scancode == SDL_SCANCODE_DOWN)
		{
			app->down = 0;
            
		}

		if (event->keysym.scancode == SDL_SCANCODE_LEFT)
		{
			app->left = 0;
		}

		if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
		{
			app->right = 0;
		}

        if (event->keysym.scancode == SDL_SCANCODE_SPACE)
        {
	        app->fire = 0;
         
        }

	}
}


void playerMovement(Application *app, Player *player)
{ 

    player->moving = 0;
    player->face_left = 0;
    player->face_right = 0;

    app->time ++; 
    
    if (player->alive == 0)
    {
        if (player->reloading > 0)
	    {
		    player->reloading--;
	    }
    
    	if (app->up)
		{
			player->y -= PLAYER_MOVEMENT_SPEED;
            player->moving = 1;
		}

		if (app->down)
		{
			player->y += PLAYER_MOVEMENT_SPEED;
            player->moving = 1;
		}

		if (app->left)
		{
			player->x -= PLAYER_MOVEMENT_SPEED;
            player->moving = 1;
            player->face_left = 1;

		}

		if (app->right)
		{
			player->x += PLAYER_MOVEMENT_SPEED;
            player->moving = 1;
            player->face_right = 1;

		}

        if(app->fire)
        {   
            if(player->reloading==0)
            {   

                fireBullet(app, player);
                
            }
        }
    } 

// |======= Player bullet movement ======= | 

        Bullet* curr_bullet; 

        curr_bullet = app->start_bullet->next;
        
        while(curr_bullet != NULL)
        {   
        
            curr_bullet->y -= 10; 

            printf("Current bullet is at y: %f \n", curr_bullet->y);
         
            curr_bullet = curr_bullet ->next;
        
        }

// |======= Player bullet delete ======= | 

    deleteBullets(app->start_bullet, app->start_bullet->next, &(app->end_bullet));

}


void doAnimation(Application *app, Player *player)
{

// |======= Animate player ======= | 

//  Animate player when shot
if(player->alive==1){
    if(app->time % 10 == 0){
            switch(player->animFrame){
            case 4:
                player->animFrame = 5; 
                break;
            case 5:
                player->animFrame = 6; 
                break;
            case 6:
                player->animFrame = 7; 
                break;
            case 7:
                player->animFrame = 8; 
                break;
            case 8:
                player->animFrame = 9; 
                break;
            case 9:
                player->animFrame = 10; 
                break;
            case 10:
                break;
            default:
                player->animFrame = 5;
            }
        }
// Animate player when moving 

} else if (player->moving == 1){

// Animate player when strafing left or right 

    if(player->face_left == 1 || player->face_right == 1){
        if(app->time % 10 == 0){
            if(player->animFrame == 2){
                player->animFrame = 3;
            }else if(player->animFrame == 3){
                player->animFrame = 2;
            }else{
                player->animFrame = 2;
            }
        }

    }else{

// |======= Animate player when walking forward or downward

        if(app->time % 10 == 0){
            if(player->animFrame == 0){
                 player->animFrame = 1;
             }else if(player->animFrame == 1){
                player->animFrame = 0;
             }else{
                player->animFrame = 0;
             }
         }
    }

// |======= Return player to default state if not shot or moving 
}
else
{
    player->animFrame = 0;
}

// |======= Animate enemies

for(Player* iter_player  = app->start_enemy->enemy_next; iter_player != NULL; iter_player = iter_player->enemy_next){
    if(iter_player->alive == 1){
        if(app->time % 10 == 0){
            if (iter_player->animFrame == 0){
                iter_player->animFrame = 1;
            } else if (iter_player->animFrame == 1){
                iter_player->animFrame = 2;
            } else if (iter_player->animFrame == 2){
                iter_player->animFrame = 3; 
            }else if (iter_player->animFrame == 3){
                iter_player->animFrame = 4;
            }
        }
    }
}
   
}



void positionCamera(Application *app, Player *player)
{
        
        app->camera.y = player->y - 240; 

        if(app->camera.y < 0){
            app->camera.y = 0;
        }
        if(app->camera.x < 0){
            app->camera.x = 0;
        }

        SDL_QueryTexture(app->background, NULL, NULL, &app->x, &app->y);
        
        if(app->camera.x + app->camera.w >= app->x)
        {
            app->camera.x = app->x - 640; 
        }
        if(app->camera.y + app->camera.h >= app->y)
        {
            app->camera.y = app->y - 480; 
        }

}


void enemyMovement(Application *app, Player *player)
{

// |======= Enemy bullet movement ======= | 

    Bullet* curr_bullet_enemy; 

    curr_bullet_enemy = app->start_bullet_enemy->next;
        
    while(curr_bullet_enemy != NULL){

        curr_bullet_enemy->y += 10 * curr_bullet_enemy->dy;
        curr_bullet_enemy->x += 10 * curr_bullet_enemy->dx;
        curr_bullet_enemy = curr_bullet_enemy ->next; 
    }


    // |======= Enemy bullet delete ======= | 

    deleteBullets(app->start_bullet_enemy, app->start_bullet_enemy->next, &(app->end_bullet_enemy));

    // |======= Movement of Enemies ======= | 

    for(Player* iter_enemy  = app->start_enemy->enemy_next; iter_enemy != NULL; iter_enemy = iter_enemy->enemy_next){

        if(iter_enemy->alive == 0){

            float dirx;
            float diry; 
            float angle_x;
            float angle_y;
            float run_x;
            float run_y;
            float hyp;

            dirx = player->x - iter_enemy->x;
            diry = player->y - iter_enemy->y;

            hyp = sqrt(dirx*dirx + diry*diry);

            run_x = dirx/hyp;
            run_y = diry/hyp;

// If the enemy is not within distance of the player, move the enemy toward the player
            if(fabsf(dirx) >= 50 && fabsf(diry) >= 50){

                iter_enemy->x += run_x * 2;
                iter_enemy->y += run_y * 2;
            }

//|========= Calculate direction and angle of enemy bullet

            iter_enemy->x_aim = run_x;
            iter_enemy->y_aim = run_y; 
            
// Calculate arctan of the x and y coordinate of the distance between the player and enemy
// Convert from radians to degrees with 180/pi

            angle_x = iter_enemy->x - player->x + PLAYER_WIDTH/2;
            angle_y = iter_enemy->y - player->y + PLAYER_HEIGHT/2;

            iter_enemy->bullet_angle =  (atan2f(angle_y,angle_x)) * (180/3.14);

            if(iter_enemy->bullet_angle >= 90){

                iter_enemy->bullet_angle = iter_enemy->bullet_angle - 90;

            }else{

                iter_enemy->bullet_angle = iter_enemy->bullet_angle + 270;
            }
            
            iter_enemy->bullet_angle = fmodf(iter_enemy->bullet_angle + 360, 360);
            
            if (iter_enemy->reloading > 0){
		        iter_enemy->reloading--;
            }

            if(iter_enemy->reloading==0){
                fireBulletEnemy(app, iter_enemy);
            }
        }
    
    }

}


bool doInput(Application *app, bool *running)
{
	SDL_Event event;

	while (SDL_PollEvent(&event)){
		switch (event.type){
			case SDL_QUIT:
            case SDLK_ESCAPE:
				running = false;
				break;
            case SDL_KEYDOWN: 
                doKeyDown(&event.key, app);
                break;
            case SDL_KEYUP:
                doKeyUp(&event.key, app);
                break;
			default:
				break;
		}
	}

    return running;
}


void drawFigures(Application *app, Player *player)
{

//|======= Draw player 

    SDL_RenderCopy(app->renderer, app->background, &app->camera, NULL);

// If the player is facing left, flip the animation frames (facing right) horizontally. 

    SDL_RendererFlip flip;

    if(player->face_left == 1){
        flip = SDL_FLIP_HORIZONTAL;
    }else{
        flip = SDL_FLIP_NONE;
    }

// Centres the player in the middle of the screen 

    SDL_Rect rect_player = {player->x - app->camera.x, player->y - app->camera.y, PLAYER_WIDTH , PLAYER_HEIGHT};

    SDL_RenderCopyEx(app->renderer, app->texture_player[player->animFrame], NULL, &rect_player, 0, NULL, flip);


//|======= Draw enemy bullets

    Bullet* curr_bullet_enemy_iter = app->start_bullet_enemy->next; 

    while(curr_bullet_enemy_iter != NULL){

        SDL_Rect bullet_enemy = {curr_bullet_enemy_iter->x - app->camera.x, curr_bullet_enemy_iter->y - app->camera.y, 8 , 8};

// The enemy bullets are rotated by the angle they are pointed at the player
 
        SDL_RenderCopyEx(app->renderer, app->bullet_texture, NULL, &bullet_enemy, curr_bullet_enemy_iter->angle, NULL, 0);

        curr_bullet_enemy_iter = curr_bullet_enemy_iter->next;
    }

//|======= Draw player bullets

    Bullet* curr_bullet = app->start_bullet->next; 
    
    while(curr_bullet != NULL){

        SDL_Rect bullet = {curr_bullet->x - app->camera.x, curr_bullet->y - app->camera.y, 8 , 8};
        
        SDL_RenderCopyEx(app->renderer, app->bullet_texture, NULL, &bullet, curr_bullet->angle, NULL, 0);

        curr_bullet = curr_bullet->next;
    }

//|======= Draw enemies

    Player* curr_enemy = app->start_enemy->enemy_next; 
    
    while(curr_enemy != NULL){

        SDL_Rect enemy_multi = {curr_enemy->x - app->camera.x, curr_enemy->y - app->camera.y, 48 , 48};

        SDL_RenderCopyEx(app->renderer, app->texture_enemy[curr_enemy->animFrame], NULL, &enemy_multi, 0, NULL, 0);

        curr_enemy = curr_enemy->enemy_next;
    }

}


void spawnEnemy(Application *app, Player *player)
{
    Player* new_enemy = malloc(sizeof(Player));

    if (new_enemy == NULL){
        printf("Insufficient memory to allocate for new enemy \n");
        exit(1);
    }

    new_enemy->x = random_int(0, 480);
    new_enemy->y = random_int(0, player->y - 600);
    new_enemy->alive = 0;
    new_enemy->animFrame = 0;
    new_enemy->reloading = 40;
    new_enemy->bullet_angle = 0;
    new_enemy->x_aim = 0;
    new_enemy->y_aim = 0;
    new_enemy->enemy_next = NULL;

    new_enemy->enemy_prev = app->end_enemy;

    app->end_enemy->enemy_next = new_enemy; 

    app->end_enemy = new_enemy; 

}


int main (int argc, char *argv[])
{

// |======= Declare & initialise game variables

    Application app; 
    
    Player player;

    memset(&app, 0, sizeof(Application));

    memset(&player, 0, sizeof(Player));

    initSDL(&app);

    bool running = true;

    app.time = 0;

    // Initialise player

    player.x = 160;

    player.y = 1680;

    player.alive = 0;

    player.moving = 0;

    player.face_left = 0;

    player.face_right = 0;

    app.texture_player[0] = loadTexture(&app, "Textures/man1_v2.png");

    app.texture_player[1] = loadTexture(&app, "Textures/man2_v2.png");

    app.texture_player[2] = loadTexture(&app, "Textures/man_side0.png");

    app.texture_player[3] = loadTexture(&app, "Textures/man_side1.png");

    app.texture_player[4] = loadTexture(&app, "Textures/player_shot1.png");

    app.texture_player[5] = loadTexture(&app, "Textures/player_shot2.png");

    app.texture_player[6] = loadTexture(&app, "Textures/player_shot3.png");

    app.texture_player[7] = loadTexture(&app, "Textures/player_shot4.png");

    app.texture_player[8] = loadTexture(&app, "Textures/player_shot5.png");

    app.texture_player[9] = loadTexture(&app, "Textures/player_shot6.png");

    app.texture_player[10] = loadTexture(&app, "Textures/player_shot7.png");

    // Initialise enemy 

    Player* dummy_enemy = malloc(sizeof(Player));

    dummy_enemy->enemy_next = NULL;
    dummy_enemy->enemy_prev = NULL;
    app.start_enemy = dummy_enemy; 
    app.end_enemy = dummy_enemy; 
    
    app.texture_enemy[0] = loadTexture(&app, "Textures/enemy.png");

    app.texture_enemy[1] = loadTexture(&app, "Textures/enemy_shot1.png");
    
    app.texture_enemy[2] = loadTexture(&app, "Textures/enemy_shot2.png");

    app.texture_enemy[3] = loadTexture(&app, "Textures/enemy_shot3.png");

    app.texture_enemy[4] = loadTexture(&app, "Textures/enemy_shot4.png");

    app.bullet_texture = loadTexture(&app, "Textures/bullet.png");

    // Initialise background / camera

    app.background = loadTexture(&app, "Textures/background.png");

    // Used for saving dimensions of background image

    app.x = 0;
    app.y = 0;

    app.camera.w = 640;
    app.camera.h = 480;

    // Initialise player bullet

    Bullet *dummy_bullet;

   dummy_bullet = malloc(sizeof(Bullet));

   memset(dummy_bullet, 0, sizeof(Bullet));

    if(dummy_bullet == NULL){
        printf("insufficient memory \n");
    }

    Bullet *dummy_bullet_start;

   dummy_bullet_start = malloc(sizeof(Bullet));

   memset(dummy_bullet_start, 0, sizeof(Bullet));

    if(dummy_bullet_start == NULL){
        printf("insufficient memory \n");
    }


    dummy_bullet_start -> prev = NULL;
    dummy_bullet->next = NULL;
    dummy_bullet_start -> next =  dummy_bullet;
    dummy_bullet->prev = dummy_bullet_start;
    app.end_bullet = dummy_bullet; 
    app.start_bullet = dummy_bullet_start; 

    // Initialise enemy bullet

    Bullet* dummy_bullet_enemy = malloc(sizeof(Bullet));

        if(dummy_bullet_enemy == NULL){
        printf("insufficient memory \n");
    }   

    memset(dummy_bullet_enemy, 0, sizeof(Bullet));

    dummy_bullet_enemy->next = NULL;
    dummy_bullet_enemy->prev = NULL;
    app.end_bullet_enemy = dummy_bullet_enemy; 
    app.start_bullet_enemy = dummy_bullet_enemy; 

    while(running){

        prepareScene(&app);

        running = doInput(&app, &running);

        playerMovement(&app, &player);

        enemyMovement(&app, &player);

        doAnimation(&app, &player);

        positionCamera(&app, &player);

        if(app.time % 1000 == 0){
            spawnEnemy(&app, &player);
        }

        collisionDetect(&app, &player);

        drawFigures(&app, &player);

        presentScene(&app);

        SDL_Delay(5);

    }

    SDL_DestroyWindow(app.window);

    SDL_DestroyRenderer(app.renderer);

    SDL_Quit();

    return 0;
}