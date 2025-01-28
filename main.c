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
typedef enum {LOGO, TITLE, GAMESTART, GAMEPLAY, ENDING} GameState;

int main(void){


    Texture splash_screen = LoadTexture("$PWD/resources/meteor.png");
    IsTextureReady(splash_screen);
  /*Texture2D splash_screen = LoadTexture("resources/meteor.png");*/
  /*Font jetbrains =*/
  /*    LoadFont("/usr/share/fonts/TTF/UbuntuNerdFont-Bold.ttf");*/
  Font default_font = GetFontDefault();
  InitWindow(WIDTH, HEIGHT, "simple_gamer");

  GameState state = LOGO; 
  SetExitKey(KEY_BACKSPACE);
  while(!WindowShouldClose()){
    BeginDrawing();
    ClearBackground((Color)BACKGROUND_COLOR);
    switch (state) {
        case LOGO:
            // Call a function for the logo screen if needed
            draw_logo_screen(&splash_screen);
            if(IsKeyPressed(KEY_ENTER)){
                    state = GAMESTART;
                }
            break;

        case TITLE:
            title_screen(); // Uncomment this function or implement it
            break;

        case GAMESTART:
            start_screen(default_font); // Ensure this is reachable
            break;

        case GAMEPLAY:
            main_game_loop();
            break;

        case ENDING:
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


void start_screen(Font font){
  ClearBackground(BLACK);
  float previous_time = GetFrameTime();
  Vector2 new_game_position = {WIDTH /2.0, HEIGHT/2.0};
  DrawTextPro(font,"NEW GAME", new_game_position, (Vector2){0, 0}, 0.0f, 14, 1.0, BLUE);
}
void draw_logo_screen(Texture2D *texture){
  float previous_time = GetFrameTime();
  Rectangle meteor = {0, 0, 32, 32};
  for(float i =0; i < previous_time * GetFrameTime(); i++){
    DrawTextureRec(*texture, meteor, (Vector2){WIDTH/2.0, HEIGHT/2.0}, WHITE);
    
  };
}
void main_game_loop(void) {
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
