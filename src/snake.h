#ifndef SNAKE_H
#define SNAKE_H

#include "utils.h"
#include "screen.h"
#include "font.h"
#include "keyboard.h"

/* ---------------- Defines ---------------- */

#define HORZ_SQUARES    20
#define VERT_SQUARES    15

#define GAME_OVER       1

#define FPS             15

/* Y border is uneven that's why theres a Start and a End */
#define Y_BORDER_S      16

#define SQUARE_SIZE     MIN(SCREEN_WIDTH / HORZ_SQUARES, \
                        (SCREEN_HEIGHT - Y_BORDER_S) / VERT_SQUARES)

#define Y_BORDER_E      (Y_BORDER_S + (VERT_SQUARES * SQUARE_SIZE))
#define X_BORDER        ((SCREEN_WIDTH - (SQUARE_SIZE * HORZ_SQUARES)) / 2)

/* ----------------- Types ----------------- */

struct Position {
    uint8_t x;
    uint8_t y;
};

struct Snake {
    struct Position body[300];
};

/* ---------- Function prototypes ---------- */

/* Meant to be ran only once */
void init_game(void);

/* Responsible for updating the snake, score, apple and game status */
void game_update(void);

/* Resets the game after winning/losing */
void game_reset(void);

/* Initizalizes the board by writting the score and drawing the actuall game board */
void init_board(void);

/* Responsible for drawing everything */
void draw_board(void);

/* Semi-randomly generates a new apple */
void new_apple(void);

/* Sets the snake initial position */
void init_snake(void);

/* Updates the coords of the snake's body and performs checking on moves, boundaries and apples */
void snake_update(void);

#endif /* SNAKE_H */