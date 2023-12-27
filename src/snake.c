#include "snake.h"

extern uint32_t tick;
extern uint8_t *video_memory;
extern uint8_t key;

struct Snake snake;
struct Position apple;

uint16_t best, score, snake_size = 2, last_key;
bool game_status;


/* temp funtion for debugging */
void print_middle(const char * title, uint8_t num) {
    char str[4] = {0};
    uint8_t i = 0;
    for(i = 0 ; title[i] != 0 ; i++);
    int_to_string(num, str);
    print_string(title, 100, 4, VC_WHITE);
    print_string(str, 150 , 4, VC_WHITE);
}

/*
Current bugs and issues:
    - The snake can go through itself and do other weird "illegal" movements
    - The snake "lags" behind when eating and apple
    - Need to implement double buffering
    - Need to implement the popups
    - Would be nice for the snake head to either have more texture or be a different colour
*/


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
    print_middle("lst k", last_key);

    draw_board();
}

void game_reset(void) {
    best = MAX(best, score);
    score = 0, game_status = 0, key = 0, snake_size = 2;

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
    /* TODO These could just be defines */
    uint32_t y_border_s = 16;
    uint32_t square_size = MIN(SCREEN_WIDTH / HORZ_SQUARES, (SCREEN_HEIGHT - y_border_s) / VERT_SQUARES)

    uint32_t x_border = ((SCREEN_WIDTH - (square_size * HORZ_SQUARES)) / 2);
    uint32_t y_border_e = (y_border_s + (VERT_SQUARES * square_size));

    for (uint16_t y = y_border_s ; y <= y_border_e ; y++) {
        for (uint16_t x = x_border ; x <= SCREEN_WIDTH - x_border ; x++) {

            /* Draw grid */
            if ((x - x_border) % square_size == 0 || (y - y_border_s) % square_size == 0) {
                draw_pixel(x , y, VC_WHITE);
                continue;
            }

            /* Draw apple */
            if (apple.x == (x - x_border) / square_size && apple.y == (y - y_border_s) / square_size) {
                draw_pixel(x , y, VC_RED);
                continue;
            }

            /* Draw the snakes body */
            for (uint16_t snake_i = 0 ; snake.body[snake_i].x != 254 ; snake_i++) {
                if (snake.body[snake_i].x == (x - x_border) / square_size && snake.body[snake_i].y == (y - y_border_s) / square_size) {
                    draw_pixel(x , y, VC_GREEN);
                }
            }
        }
    }
    sleep(1); /* TODO remove this */
}

/* TODO implement checking to spawn the apple not in the snakes body */
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

    /* Mark the unused body parts with 254 */
    for (uint16_t i = 3 ; i < 300 ; i++) {
        snake.body[i].x = 254;
        snake.body[i].y = 254;
    }
}

/* Updates the coords of the snake's body and makes the snake bigger if an apple is eaten */
/* also calls new_apple*/
void snake_update(void) {
    uint8_t cur_key = key;
    struct Position old = snake.body[0];

    /* Check if the snake hit a wall, special case when key == 0 for when the game start */
    if ((snake.body[0].y == 0 && cur_key == 'w') ||
        (snake.body[0].x == 0 && cur_key == 'a') ||
        (snake.body[0].y == VERT_SQUARES - 1 && cur_key == 's') ||
        (snake.body[0].x == HORZ_SQUARES - 1 && (cur_key == 'd' || cur_key == 0))) {
            game_status = GAME_OVER;
            return;
    }
    /* Check if snake ate an apple */
    if (snake.body[0].x == apple.x && snake.body[0].y == apple.y) {
        snake_size++, score++;
        new_apple();
    }


    /* Loop through snake size*/
    for (uint16_t i = 1 ; i != snake_size + 1 ; i++) {
        struct Position temp = snake.body[i];
        snake.body[i] = old;
        old = temp;
    }

    /* If no key has been pressed yet, go foward */
    cur_key = cur_key == 0 ? 'd' : cur_key;

    /* Update head direction */
    switch (cur_key) {
    case 'w':
        if (snake.body[0].y > 0 && last_key != 's') {
            snake.body[0].y--;
        }
        break;
    case 'a':
        if (snake.body[0].x > 0 && last_key != 'd') {
            snake.body[0].x--;
        }
        break;
    case 's':
        if (snake.body[0].y < VERT_SQUARES - 1 && last_key != 'w') {
            snake.body[0].y++;
        }
        break;
    case 'd':
        if (snake.body[0].x < HORZ_SQUARES - 1 && last_key != 'a') {
            snake.body[0].x++;
        }
        break;
    default:
        return;
    }

    last_key = cur_key;
}
