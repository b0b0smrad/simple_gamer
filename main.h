#ifndef MAIN_H
#define MAIN_H

#include <raylib.h>
// **** **** TIMER RELATED FUNCTION **** ****
//




#define GAME_OVER -1
#define SPEED 63.5
#define HEIGHT 1024
#define WIDTH 1240
#define BACKGROUND_COLOR {0, 9, 87, 0}
typedef enum {LOGO, TITLE, GAMESTART, GAMEPLAY, SETTINGS} GameState;

typedef struct Player {
    Vector2 pos;
    Vector2 delta_pos;
    Vector2 origin;
    int direction;
    float rotation;
    float speed;
    bool moving;
    float health;
    Texture2D texture;
    Rectangle player_rec;
    BoundingBox constraints;

}Player;
typedef struct {
    float frameCounter;
    int currentFrame;
    int totalFrames;
} AnimTimer;
//
#define MAX_ROCKETS 10  // Adjust as needed

typedef struct {
    Vector2 position;
    Vector2 velocity;
    float lifetime; 
    bool active;
} Rocket;
void shoot_rocket(AnimTimer *lifetime, Player *rocketship);

int update_timer(AnimTimer *timer, float duration);
// Function declarations
//
void draw_logo_screen_2(AnimTimer *logoAnim, Texture2D *texture);
void main_game_loop(AnimTimer *rocket_timer, AnimTimer *timer, Player *player);
void title_screen(void);
int start_screen(Font font);
void draw_logo_screen(int timer, Texture2D *texture);
int draw_ending_screen(Font font);
void draw_error_screen(void);
void shot_rocket(AnimTimer *lifetime, Texture projectile, Player *rocketship);
// ** ** ** **  BUTON RELATED FUNCTIONS * * * * * *//
typedef struct {
				bool active;
				float size;
				Rectangle box;



} Button;

#endif // MAIN_H
