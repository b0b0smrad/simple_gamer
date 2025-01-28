#ifndef MAIN_H
#define MAIN_H

#include <raylib.h>
// **** **** TIMER RELATED FUNCTION **** ****
//

typedef struct {
    float frameCounter;
    int currentFrame;
    int totalFrames;
} AnimTimer;
//
int update_timer(AnimTimer *timer, float duration);
// Function declarations
//
void draw_logo_screen_2(AnimTimer *logoAnim, Texture2D *texture);
void main_game_loop(void);
void title_screen(void);
int start_screen(Font font);
void draw_logo_screen(int timer, Texture2D *texture);
void draw_ending_screen(void);
void draw_error_screen(void);
// ** ** ** **  BUTON RELATED FUNCTIONS * * * * * *//
typedef struct {
				bool active;
				float size;
				Rectangle box;



} Button;

#endif // MAIN_H
