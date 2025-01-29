#include "main.h"
#include <ctype.h>
#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <raymath.h>

Rocket rockets[MAX_ROCKETS] = {0};
void UpdateCharacterMovement(Player *player, Rectangle *animation);
int main(void){

    InitWindow(WIDTH, HEIGHT, "simple_gamer");
    SetTargetFPS(60);
    AnimTimer logoAnim = { 
            .frameCounter = 0,
            .currentFrame = 0,
            .totalFrames = 7  // Since your sprite has 7 frames
        };
    AnimTimer player_animation = { 
            .frameCounter = 0,
            .currentFrame = 0,
            .totalFrames = 8  // Since your sprite has 7 frames
        };
AnimTimer rocket_timer = {
        .frameCounter = 0,
        .currentFrame = 0,
        .totalFrames = 4
    };
  char texture[] = "resources/meteor.png" ;
  char spaceship[] ="resources/spaceship_sprite.png";

  Texture2D splash_screen = LoadTexture(texture);
  Texture2D player_texture = LoadTexture(spaceship);
  IsTextureReady(splash_screen);
  IsTextureReady(player_texture);

Player player = {
    .pos = {0, 0},
    .speed = SPEED,
    .delta_pos = {0,0},
    .health = 500,
    .origin = {64, 64},
    .rotation = 0,
    .moving = false,
    .texture = player_texture,
    
    
};
  /*Texture2D splash_screen = LoadTexture("resources/meteor.png");*/
  /*Font jetbrains =*/
  /*    LoadFont("/usr/share/fonts/TTF/UbuntuNerdFont-Bold.ttf");*/
  Font default_font = GetFontDefault();
  Font JetBrains = LoadFont("/usr/share/fonts/TTF/JetBrainsMonoNerdFont-Bold.ttf");

  GameState state = LOGO; 
  SetExitKey(KEY_BACKSPACE);
  while(!WindowShouldClose()){
    BeginDrawing();
    player.player_rec= (Rectangle){player.pos.x, player.pos.y, 128,128};
    switch (state) {
        case LOGO:
            // Call a function for the logo screen if needed
            DrawText(TextFormat("%d", logoAnim.totalFrames),20, 40, 20, WHITE);
            DrawText(TextFormat("%fl", logoAnim.frameCounter),20, 80, 20, WHITE);
            /*draw_logo_screen(animation, &splash_screen);*/
            draw_logo_screen_2(&logoAnim,&splash_screen);
            if(IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT) *2){
                    state = GAMESTART;
                }
            break;

        case TITLE:
            title_screen(); // Uncomment this function or implement it
            break;

        case GAMESTART:
                {

            /*start_screen(JetBrains);*/
            switch(start_screen(JetBrains)) {
                case 1:
                    state = GAMEPLAY;
                    break;
                case 2:
                    state = SETTINGS;
                    break;
                case 3:

                        CloseWindow();
                        break;
            }


                }
            break;

        case GAMEPLAY:
            main_game_loop(&rocket_timer,&player_animation, &player);
                if (IsKeyPressed(KEY_ESCAPE)){
                    state = SETTINGS;
                }
            break;

        case SETTINGS:
            // Call a function for the ending screen if needed
            /*start_screen(JetBrains);*/
            switch(draw_ending_screen(JetBrains)) {
                case 1:
                    state = GAMEPLAY;
                    break;
                case 2:
                    state = SETTINGS;
                    break;
                case 3:
                        state = GAMESTART;
                        break;
            }


                
            break;
        

        default:
            // Handle unexpected GameState values
            draw_error_screen();
            break;
    }


    EndDrawing();
    }
  /*UnloadFont(jetbrains);*/
  /*UnloadTexture(splash_screen);*/
  return 0;
}


int update_timer(AnimTimer *timer, float duration) {
    timer->frameCounter += GetFrameTime();
    float frameDuration = duration/timer->totalFrames; 
    
    if ((float)timer->frameCounter >= 0.18f) {  // 7 frames in your sprite
    /*if ((int)timer->frameCounter++ % 10 != 0){*/
        timer->frameCounter = 0;
        timer->currentFrame++;
        if (timer->currentFrame >= timer->totalFrames) {  // Reset after last frame
            timer->currentFrame = 0;
        }
    }
    return timer->currentFrame;
}
int start_screen(Font font){
  ClearBackground(BLACK);
    BoundingBox box1;
    
    static float size_new_game = 25;
    static float size_settings= 25;
    static float size_exit = 25;
    static bool is_under_game = false;
    static bool is_under_settings= false;
    static bool is_under_exit = false;
  float previous_time = GetFrameTime();
  Vector2 new_game_position = {WIDTH /2.0, HEIGHT/2.0};
float text_width = MeasureText("NEW GAME", size_new_game);
  Rectangle new_game_rec = {new_game_position.x - 50, new_game_position.y, 140,30};
  Vector2 settings_position = {WIDTH /2.0, (HEIGHT/2.0)+40};
  Rectangle settings_rec= {new_game_position.x - 50, new_game_position.y+40, 140,30};
  Vector2 exit_position = {WIDTH /2.0, (HEIGHT/2.0)+80};
  Rectangle exit_rec = {new_game_position.x - 50, new_game_position.y+80, 140,30};
  is_under_game = CheckCollisionPointRec(GetMousePosition(), new_game_rec);
  is_under_settings = CheckCollisionPointRec(GetMousePosition(), settings_rec);
  is_under_exit = CheckCollisionPointRec(GetMousePosition(), exit_rec);
  size_new_game = is_under_game? Lerp(size_new_game, 32.0f, 0.2f): 25;
  size_settings = is_under_settings? Lerp(size_settings, 32.0f, 0.2f): 25;
  size_exit = is_under_exit ? Lerp(size_exit , 32.0f, 0.2f): 25;
  /*DrawRectangleRec(new_game_rec, RED);*/
  /*DrawRectangleRec(settings_rec, RED);*/
  /*DrawRectangleRec(exit_rec, RED);*/
  DrawTextPro(font,"NEW GAME", new_game_position, (Vector2){45, 0}, 0.0f, size_new_game, 1.1, BLUE);
  DrawTextPro(font,"SETTINGS", settings_position, (Vector2){45, 0}, 0.0f, size_settings, 1.1, BLUE);
  DrawTextPro(font,"EXIT", exit_position, (Vector2){25, 0}, 0.0f, size_exit, 1.1, BLUE);
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (CheckCollisionPointRec(GetMousePosition(), new_game_rec)) {
            return 1;
        }
        if (CheckCollisionPointRec(GetMousePosition(), settings_rec)) {
            return 2;
        }
        if (CheckCollisionPointRec(GetMousePosition(), exit_rec)) {
            return 3;
        }
    }    return 0;
}


//
void draw_logo_screen(int timer, Texture2D *texture){
  float previous_time = GetFrameTime();
  /*Rectangle meteor = {0, 0, 32, 32};*/
  int animation = timer;
  Rectangle frameRec = { 0.0f, 0.0f, (float)texture->width/7, (float)texture->height};
  frameRec.x += (float)animation *(float)texture->width;
  DrawTextureRec(*texture, frameRec, (Vector2){WIDTH/2.0, HEIGHT/2.0}, WHITE);
}
void draw_logo_screen_2(AnimTimer *logoAnim, Texture2D *texture) {
    ClearBackground(BLACK);
    int currentFrame = update_timer(logoAnim, 8.0f);  // 8 seconds total duration

    /*SetTextureFilter(*texture, );*/
    Rectangle frameRec = { 0.0f, 0.0f, (float)texture->width/7, (float)texture->height};
    frameRec.x += (float)logoAnim->currentFrame*(float)texture->width/7;
    Vector2 position = {
        WIDTH/2.0f ,
        HEIGHT/2.0f 
    };

    DrawTexturePro(*texture, frameRec, (Rectangle){WIDTH/2.0,HEIGHT/2.0, 128, 128}, (Vector2){50,50}, 0.0f, WHITE);
    /*DrawTextureRec(*texture, frameRec, position, WHITE);*/
}
void main_game_loop(AnimTimer *rocket_timer, AnimTimer *timer, Player *player) {
    ClearBackground(BLACK);
    // Placeholder logic
    timer->currentFrame= update_timer(timer, 8.0f);  // 8 seconds total duration
    UpdateCharacterMovement(player, &player->player_rec);
    Rectangle player_rec = {0, 0, 32,32};
    player_rec.x += (float)timer->currentFrame*(float)player->texture.width/8;
    DrawTexturePro(player->texture,player_rec, player->player_rec, player->origin, player->rotation, WHITE);
    shoot_rocket(rocket_timer, player);
    DrawText("Main Game Loop", 100, 100, 20, RED);
}

void title_screen(void) {
    // Placeholder logic
    DrawText("Title Screen", 100, 100, 20, GREEN);
}

int draw_ending_screen(Font font) {
  ClearBackground(BLACK);
    BoundingBox box1;
    
    static float size_new_game = 25;
    static float size_settings= 25;
    static float size_exit = 25;
    static bool is_under_game = false;
    static bool is_under_settings= false;
    static bool is_under_exit = false;
  float previous_time = GetFrameTime();
  Vector2 new_game_position = {WIDTH /2.0, HEIGHT/2.0};
float text_width = MeasureText("NEW GAME", size_new_game);
  Rectangle new_game_rec = {new_game_position.x - 50, new_game_position.y, 140,30};
  Vector2 settings_position = {WIDTH /2.0, (HEIGHT/2.0)+40};
  Rectangle settings_rec= {new_game_position.x - 50, new_game_position.y+40, 140,30};
  Vector2 exit_position = {WIDTH /2.0, (HEIGHT/2.0)+80};
  Rectangle exit_rec = {new_game_position.x - 50, new_game_position.y+80, 140,30};
  is_under_game = CheckCollisionPointRec(GetMousePosition(), new_game_rec);
  is_under_settings = CheckCollisionPointRec(GetMousePosition(), settings_rec);
  is_under_exit = CheckCollisionPointRec(GetMousePosition(), exit_rec);
  size_new_game = is_under_game? Lerp(size_new_game, 32.0f, 0.2f): 25;
  size_settings = is_under_settings? Lerp(size_settings, 32.0f, 0.2f): 25;
  size_exit = is_under_exit ? Lerp(size_exit , 32.0f, 0.2f): 25;
  /*DrawRectangleRec(new_game_rec, RED);*/
  /*DrawRectangleRec(settings_rec, RED);*/
  /*DrawRectangleRec(exit_rec, RED);*/
  DrawTextPro(font,"CONTINUE", new_game_position, (Vector2){45, 0}, 0.0f, size_new_game, 1.1, BLUE);
  DrawTextPro(font,"SETTINGS", settings_position, (Vector2){45, 0}, 0.0f, size_settings, 1.1, BLUE);
  DrawTextPro(font,"EXIT TO START", exit_position, (Vector2){25, 0}, 0.0f, size_exit, 1.1, BLUE);
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (CheckCollisionPointRec(GetMousePosition(), new_game_rec)) {
            return 1;
        }
        if (CheckCollisionPointRec(GetMousePosition(), settings_rec)) {
            return 2;
        }
        if (CheckCollisionPointRec(GetMousePosition(), exit_rec)) {
            return 3;
        }
    }    return 0;
}

void draw_error_screen(void) {
    // Placeholder logic
    DrawText("Error Screen", 100, 100, 20, YELLOW);
}

void UpdateCharacterMovement(Player *player, Rectangle *animation){
  float frameTime = GetFrameTime();
    Vector2 input = {0, 0};
    
    // Collect input directions
    if (IsKeyDown(KEY_A)) input.x -= 1;
    if (IsKeyDown(KEY_D)) input.x += 1;
    if (IsKeyDown(KEY_W)) input.y -= 1;
    if (IsKeyDown(KEY_S)) input.y += 1;
    
    // If we're moving in both directions, normalize
    if (input.x != 0 && input.y != 0) {
        input = Vector2Normalize(input);
    }
    
    // Apply movement
    player->delta_pos.x = input.x * player->speed * frameTime*1.3;
    player->delta_pos.y = input.y * player->speed * frameTime*1.3;
    
    // Update position
    player->pos.x += player->delta_pos.x;
    player->pos.y += player->delta_pos.y;
    
    // Update rectangle
    player->player_rec.x = player->pos.x;
    player->player_rec.y = player->pos.y;
    
    // Update rotation based on movement direction
    if (input.x != 0 || input.y != 0) {
        player->rotation = atan2f(input.y, input.x) * RAD2DEG + 90;
    }
    
    // Set moving flag
    player->moving = (input.x != 0 || input.y != 0);
}

void shoot_rocket(AnimTimer *lifetime, Player *rocketship) {
    float frameTime = GetFrameTime();
    
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        // Find an available slot for a new rocket
        for (int i = 0; i < MAX_ROCKETS; i++) {
            if (!rockets[i].active) {
                float angle = (rocketship->rotation - 90) * DEG2RAD;
                rockets[i].position.x = rocketship->player_rec.x +rocketship->origin.x;
                rockets[i].position.y = rocketship->player_rec.y + rocketship->origin.y;
                rockets[i].velocity.x = cosf(angle) * Lerp(350, 250, 0.2);
                rockets[i].velocity.y = sinf(angle) * Lerp(350, 250, 0.2);
                rockets[i].lifetime = 0.5;
                rockets[i].active = true;
                break;
            }
        }
    }

    // Update and draw rockets
    for (int i = 0; i < MAX_ROCKETS; i++) {
        if (rockets[i].active) {
            rockets[i].position.x += rockets[i].velocity.x * frameTime;
            rockets[i].position.y += rockets[i].velocity.y * frameTime;
            rockets[i].lifetime -= frameTime;
            // Draw rocket (for testing, using a red circle)
            DrawCircle(rockets[i].position.x, rockets[i].position.y, 5, RED);
            
            // Deactivate if out of bounds
            if (rockets[i].lifetime <= 0) {
                rockets[i].active = false;
            }
            /*if (rockets[i].position.x < 0 || rockets[i].position.x > GetScreenWidth() ||*/
            /*    rockets[i].position.y < 0 || rockets[i].position.y > GetScreenHeight()) {*/
            /*    rockets[i].active = false;*/
            /*}*/
        }
    }
}

