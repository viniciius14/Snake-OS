#include "snake.h"

#include "timer.h"
extern uint32_t tick;
extern uint8_t *video_memory;

uint16_t best;
uint16_t score;

void game_init(void) {
    score = 0, best = 0;
    board_init();

}


/*
4
8
4 ----- 16
every 12 pixels is a square

*/
void board_init(void) {
    char str[5] = {0};

    print_string("Score: 0", 4, 4, VC_WHITE);

    int_to_string(best, str);
    print_string("Best:", 250,  4, VC_WHITE);
    print_string(str, 292 , 4, VC_WHITE);


    uint32_t y_border_s = 16;
    uint32_t square_size = SCREEN_WIDTH / HORZ_SQUARES < (SCREEN_HEIGHT - y_border_s) / VERT_SQUARES
                        ? SCREEN_WIDTH / HORZ_SQUARES : (SCREEN_HEIGHT - y_border_s) / VERT_SQUARES;

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

void update_board(void) {
    screen_clear(VC_BLACK);

    char str[4] = {0};

    int_to_string(score, str);
    print_string("Score:", 4, 4, VC_WHITE);
    print_string(str, 54 , 4, VC_WHITE);

    print_string("Best:", 250,  4, VC_WHITE);
    print_string("123", 292 , 4, VC_WHITE);
}