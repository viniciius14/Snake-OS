#include "snake.h"

extern uint32_t tick;
extern uint8_t *video_memory;
extern uint8_t key;

struct Snake snake;
struct Position apple;

uint16_t best, score;


void game_init(void) {
    score = 0, best = 0;

    board_init();
    snake_init();

    // /* Game loop */
    // while (1) {
    //     if (game_status() == GAME_OVER) {
    //         if (score > best) {
    //             best = score;
    //             draw_popup("New Highscore Achieved!\nPress any key to play again");
    //         } else {
    //             draw_popup("You lost.\nPress any key to play again", VC_RED);
    //         }

            
    //     }

    //     if (score == 300) {
    //         draw_popup("Congrats u won!\nPress any key to play again");
    //     }

    //     game_update();


    // }


}

void game_update(void) {
    snake_update();

    screen_clear(VC_BLACK);

    char str[4] = {0};

    int_to_string(score, str);
    print_string("Score:", 4, 4, VC_WHITE);
    print_string(str, 54 , 4, VC_WHITE);

    // print_string("Best:", 250,  4, VC_WHITE);
    // print_string("123", 292 , 4, VC_WHITE);

    draw_board();
}

void game_reset(void) {
    score = 0;
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

void draw_board(void) {
    uint32_t y_border_s = 16;
    uint32_t square_size = MIN(SCREEN_WIDTH / HORZ_SQUARES, (SCREEN_HEIGHT - y_border_s) / VERT_SQUARES)

    uint32_t x_border = ((SCREEN_WIDTH - (square_size * HORZ_SQUARES)) / 2);
    uint32_t y_border_e = (y_border_s + (VERT_SQUARES * square_size));

    for (uint32_t y = y_border_s ; y <= y_border_e ; y++) {
        for (uint32_t x = x_border ; x <= SCREEN_WIDTH - x_border ; x++) {
            if ((x - x_border) % square_size == 0 || (y - y_border_s) % square_size == 0) {
                draw_pixel(x , y, VC_WHITE);
            }
        }
    }
}

void new_apple(void) {

}


void snake_init(void) {
    snake.body[0].x = 4;
    snake.body[0].y = 7;

    snake.body[1].x = 3;
    snake.body[1].y = 7;

    snake.body[2].x = 2;
    snake.body[2].y = 7;
}

void snake_update(void) {

}

void snake_reset(void) {

}

uint8_t game_status(void) {

}
