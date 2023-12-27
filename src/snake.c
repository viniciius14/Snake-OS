#include "snake.h"

extern uint32_t tick;
extern uint8_t *video_memory;
extern uint8_t key;

struct Snake snake;
struct Position apple;

uint16_t best, score;
bool game_status;

uint8_t calls = 0;

void game_init(void) {
    score = 0, best = 0, game_status = 0;
    new_apple();
    snake_init();
    board_init();

    /* Game loop */
    while (1) {
        if (game_status == GAME_OVER) {
            if (score > best) {
                draw_popup("New Highscore Achieved!\nPress any key to play again", VC_RED);
            } else {
                draw_popup("You lost.\nPress any key to play again", VC_RED);
            }
            game_reset();
        }

        if (score == 300) {
            draw_popup("Congrats u won!\nPress any key to play again", VC_RED);
            game_reset();
        }

        game_update();
    }
}

void game_update(void) {
    snake_update();

    screen_clear(VC_BLACK);

    char str[4] = {0};

    int_to_string(score, str);
    print_string("Score:", 4, 4, VC_WHITE);
    print_string(str, 54 , 4, VC_WHITE);

    int_to_string(best, str);
    print_string("Best:", 250,  4, VC_WHITE);
    print_string(str, 292 , 4, VC_WHITE);

    draw_board();
}

void game_reset(void) {
    best = MAX(best, score);
    score = 0, game_status = 0;

    new_apple();
    snake_reset();
}

void board_init(void) {
    char str[5] = {0};

    print_string("Score: 0", 4, 4, VC_WHITE);

    int_to_string(best, str);
    print_string("Best:", 250,  4, VC_WHITE);
    print_string(str, 292 , 4, VC_WHITE);

    draw_board();
}

/* Responsible for drawing everything */
void draw_board(void) {
    uint32_t y_border_s = 16;
    uint32_t square_size = MIN(SCREEN_WIDTH / HORZ_SQUARES, (SCREEN_HEIGHT - y_border_s) / VERT_SQUARES)

    uint32_t x_border = ((SCREEN_WIDTH - (square_size * HORZ_SQUARES)) / 2);
    uint32_t y_border_e = (y_border_s + (VERT_SQUARES * square_size));

    for (uint32_t y = y_border_s ; y <= y_border_e ; y++) {
        for (uint32_t x = x_border ; x <= SCREEN_WIDTH - x_border ; x++) {

            /* Print grid */
            if ((x - x_border) % square_size == 0 || (y - y_border_s) % square_size == 0) {
                draw_pixel(x , y, VC_WHITE);
                continue;
            }

            /* Print snake body part */
            for (uint16_t snake_i = 0 ; snake.body[snake_i].x != 254 ; snake_i++) {
                if (snake.body[snake_i].x == (x - x_border) / square_size && snake.body[snake_i].y == (y - y_border_s) / square_size) {

                    draw_pixel(x , y, VC_GREEN);
                }
            }
            /* Print apple */
            if (apple.x == (x - x_border) / square_size && apple.y == (y - y_border_s) / square_size) {
                draw_pixel(x , y, VC_RED);
            }

        }
    }
    sleep(1);
}

void new_apple(void) {
    apple.x = rand() % HORZ_SQUARES;
    apple.y = rand() % VERT_SQUARES;
}


void snake_init(void) {
    /* Starting position of the snake */
    snake.body[0].x = 4;
    snake.body[0].y = 7;

    snake.body[1].x = 3;
    snake.body[1].y = 7;

    snake.body[2].x = 2;
    snake.body[2].y = 7;

    /* Mark the unused body parts with 255 */
    for (uint16_t i = 3 ; i < 300 ; i++) {
        snake.body[i].x = 254;
        snake.body[i].y = 254;
    }
}

/* Updates the coords of the snake's body and makes the snake bigger if an apple is eaten */
/* also calls new_apple*/
void snake_update(void) {
    uint8_t cur_key = key;

    /* Update head direction */
    switch (cur_key) {
    case 'w':
        if (snake.body[0].y > 0) {
            snake.body[0].y--;
        }
        break;
    case 'a':
        if (snake.body[0].x > 0) {
            snake.body[0].x--;
        }
        break;
    case 's':
        if (snake.body[0].y < VERT_SQUARES - 1) {
            snake.body[0].y++;
        }
        break;
    case 'd':
        if (snake.body[0].x < HORZ_SQUARES - 1) {
            snake.body[0].x++;
        }
        break;
    default:
        return;
    }

}

void snake_reset(void) {

}
