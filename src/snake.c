#include "snake.h"

extern uint32_t ticks;
extern uint8_t *video_memory;
extern uint8_t key;

struct Snake snake;
struct Position apple;

uint8_t last_key = 0;
uint16_t best, score, snake_size = 2;
bool game_status;

void init_game(void) {
    uint32_t last_frame = 0;

    score = 0, best = 0, game_status = 0;

    new_apple();
    snake_init();
    board_init();

    /* Game loop */
    while (1) {
        const uint32_t now = ticks;

        if ((now - last_frame) > (TIMER_TPS / FPS)) {
            last_frame = now;

            if (game_status == GAME_OVER) {
                key = 0;

                screen_clear(VC_BLACK);
                if (score > best) {
                    print_string("New Highscore Achieved!",68, 40, VC_RED);
                    print_string("Press any key to play again.", 52, 60, VC_RED);
                    while (key == 0) {}
                } else {
                    print_string("You lost.",128, 40, VC_RED);
                    print_string("Press any key to play again.", 48, 60, VC_RED);
                    while (key == 0) {}
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

    score = 0, game_status = 0, key = 0, snake_size = 2;
    last_key = 'd';

    new_apple();
    snake_init();
}

void board_init(void) {
    char str[5] = {0};

    print_string("Score: 0", 4, 4, VC_WHITE);

    int_to_string(best, str);
    print_string("Best:", 250,  4, VC_WHITE);
    print_string(str, 292 , 4, VC_WHITE);
    draw_board();
}

void draw_board(void) {
    for (uint16_t y = Y_BORDER_S ; y <= Y_BORDER_E ; y++) {
        for (uint16_t x = X_BORDER ; x <= SCREEN_WIDTH - X_BORDER ; x++) {

            /* Draw grid */
            if ((x - X_BORDER) % SQUARE_SIZE == 0 || (y - Y_BORDER_S) % SQUARE_SIZE == 0) {
                draw_pixel(x , y, VC_WHITE);
                continue;
            }

            /* Draw apple */
            if (apple.x == (x - X_BORDER) / SQUARE_SIZE && apple.y == (y - Y_BORDER_S) / SQUARE_SIZE) {
                draw_pixel(x , y, VC_RED);
                continue;
            }

            /* Draw the snakes body */
            for (uint16_t snake_i = 0 ; snake.body[snake_i].x != 254 ; snake_i++) {
                if (snake.body[snake_i].x == (x - X_BORDER) / SQUARE_SIZE &&
                    snake.body[snake_i].y == (y - Y_BORDER_S) / SQUARE_SIZE) {
                    draw_pixel(x , y, VC_GREEN);
                }
            }
        }
    }
}

void new_apple(void) {
    apple.x = rand() % HORZ_SQUARES;
    apple.y = rand() % VERT_SQUARES;

    /* Check if the apple was spawned inside the snakes body */
    for (uint16_t i = 0 ; i != snake_size ; i++) {
        if (snake.body[i].x == apple.x && snake.body[i].y == apple.y) {
            new_apple();
        }
    }
}

void snake_init(void) {
    /* Starting position of the snake */
    snake.body[0].x = 4;
    snake.body[0].y = 7;

    snake.body[1].x = 3;
    snake.body[1].y = 7;

    snake.body[2].x = 2;
    snake.body[2].y = 7;

    /* Mark the unused body parts with 254 */
    for (uint16_t i = 3 ; i < 300 ; i++) {
        snake.body[i].x = 254;
        snake.body[i].y = 254;
    }
}

void snake_update(void) {
    uint8_t curr_key = key;
    struct Position old = snake.body[0];

    /* If no key has been pressed yet, go to the right */
    curr_key = curr_key == 0 ? 'd' : curr_key;

    /* Check if the snake hit a wall */
    if ((snake.body[0].y == 0 && curr_key == 'w') ||
        (snake.body[0].x == 0 && curr_key == 'a') ||
        (snake.body[0].y == VERT_SQUARES - 1 && curr_key == 's') ||
        (snake.body[0].x == HORZ_SQUARES - 1 && curr_key == 'd')) {
            game_status = GAME_OVER;
            return;
    }

    /* Check if the snake went into itself */
    for (uint16_t i = 1 ; i != snake_size ; i++) {
        if (snake.body[0].x == snake.body[i].x && snake.body[0].y == snake.body[i].y) {
            game_status = GAME_OVER;
            return;
        }
    }

    /* Check if the snake ate an apple */
    if (snake.body[0].x == apple.x && snake.body[0].y == apple.y) {
        snake_size++, score++;
        new_apple();
    }

    /* Hacky way to force legal movements since it's not working in the switch? */
    if(curr_key == 'w' && last_key == 's') {
        curr_key = 's';
    } else if (curr_key == 'a' && last_key == 'd') {
        curr_key = 'd';
    } else if (curr_key == 's' && last_key == 'w') {
        curr_key = 'w';
    } else if (curr_key == 'd' && last_key == 'a') {
        curr_key = 'a';
    }

    /* Update head direction */
    switch (curr_key) {
    case 'w':
        if (snake.body[0].y > 0) {  /*  && last_key != 's' */
            snake.body[0].y--;
        }
        break;
    case 'a':
        if (snake.body[0].x > 0) {  /* && last_key != 'd' */
            snake.body[0].x--;
        }
        break;
    case 's':
        if (snake.body[0].y < VERT_SQUARES - 1) {   /*  && last_key != 'w' */
            snake.body[0].y++;
        }
        break;
    case 'd':
        if (snake.body[0].x < HORZ_SQUARES - 1) {   /*  && last_key != 'a' */
            snake.body[0].x++;
        }
        break;
    case 'p':
        return;
    default:
        return;
    }

    /* Update the snakes body */
    for (uint16_t i = 1 ; i != snake_size + 1 ; i++) {
        struct Position temp = snake.body[i];
        snake.body[i] = old;
        old = temp;
    }

    last_key = curr_key;
}
