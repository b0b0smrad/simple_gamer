#ifndef MAIN_H
#define MAIN_H

#include <raylib.h>

// Function declarations
void main_game_loop(void);
void title_screen(void);
void start_screen(Font font);
void draw_logo_screen(Texture2D *texture);
void draw_ending_screen(void);
void draw_error_screen(void);

#endif // MAIN_H
