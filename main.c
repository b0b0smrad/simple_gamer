#include "main.h"
#include <ctype.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <raymath.h>



#define GAME_OVER -1
#define SPEED 3.5
#define HEIGHT 1024
#define WIDTH 1240
#define BACKGROUND_COLOR {0, 9, 87, 0}
typedef enum {LOGO, TITLE, GAMESTART, GAMEPLAY, SETTINGS} GameState;

int main(void){


    InitWindow(WIDTH, HEIGHT, "simple_gamer");
    AnimTimer logoAnim = { 
            .frameCounter = 0,
            .currentFrame = 0,
            .totalFrames = 7  // Since your sprite has 7 frames
        };

  char texture[] = "resources/meteor.png";
  Texture2D splash_screen = LoadTexture(texture);
  IsTextureReady(splash_screen);
  /*Texture2D splash_screen = LoadTexture("resources/meteor.png");*/
  /*Font jetbrains =*/
  /*    LoadFont("/usr/share/fonts/TTF/UbuntuNerdFont-Bold.ttf");*/
  Font default_font = GetFontDefault();
  Font JetBrains = LoadFont("/usr/share/fonts/TTF/JetBrainsMonoNerdFont-Bold.ttf");

  GameState state = LOGO; 
  SetExitKey(KEY_BACKSPACE);
  while(!WindowShouldClose()){
    BeginDrawing();
    /*ClearBackground((Color)BACKGROUND_COLOR);*/
    switch (state) {
        case LOGO:
            // Call a function for the logo screen if needed
            DrawText(TextFormat("%d", logoAnim.totalFrames),20, 40, 20, WHITE);
            DrawText(TextFormat("%fl", logoAnim.frameCounter),20, 80, 20, WHITE);
            /*draw_logo_screen(animation, &splash_screen);*/
            draw_logo_screen_2(&logoAnim,&splash_screen);
            if(IsKeyPressed(KEY_ENTER)){
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
                    CloseWindow();  // Use CloseWindow() instead of WindowShouldClose()
                    break;
            }


                }
            break;

        case GAMEPLAY:
            main_game_loop();
            break;

        case SETTINGS:
            // Call a function for the ending screen if needed
            draw_ending_screen();
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
    
    if (timer->frameCounter >= 0.18f) {  // 7 frames in your sprite
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
void main_game_loop(void) {
    ClearBackground(WHITE);
    // Placeholder logic
    DrawText("Main Game Loop", 100, 100, 20, RED);
}

void title_screen(void) {
    // Placeholder logic
    DrawText("Title Screen", 100, 100, 20, GREEN);
}

void draw_ending_screen(void) {
    // Placeholder logic
    DrawText("Ending Screen", 100, 100, 20, BLUE);
}

void draw_error_screen(void) {
    // Placeholder logic
    DrawText("Error Screen", 100, 100, 20, YELLOW);
}
