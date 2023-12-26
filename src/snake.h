#ifndef SNAKE_H
#define SNAKE_H

#include "utils.h"
#include "screen.h"
#include "font.h"
#include "keyboard.h"

#define HORZ_SQUARES    20
#define VERT_SQUARES    15

#define GAME_OVER       1

struct Position {
    uint8_t x;
    uint8_t y;
};

struct Snake {
    struct Position body[300];
};

/* Meant to be ran only once */
void game_init(void);


/* Responsible for updating the snake, score and apple */
void game_update(void);

/* */
void game_reset(void);

/* */
void board_init(void);

/* Responsible for drawing everything */
void draw_board(void);

/* Semi-randomly generates a new apple */
void new_apple(void);

/* */
void snake_init(void);

/* Updates the coords of the snake's body and makes the snake bigger if an apple is eaten */
void snake_update(void);

/* */
void snake_reset(void);

/* */
uint8_t game_status(void);



#endif /* SNAKE_H */