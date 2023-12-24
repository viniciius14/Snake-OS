#include "snake.h"

#include "timer.h"
extern uint32_t tick;
extern uint8_t *video_memory;

uint16_t best;
uint16_t score;

void game_init(void) {
    score = 0, best = 0;
    board_init();

    //draw board / backgound
    for(uint32_t x = 0 ; x != SCREEN_WIDTH ; x++ ) {
        for(uint32_t y = 16 ; y != SCREEN_HEIGHT; y++ ) {
            if ((x % 14 == 0 || y % 14 == 0) && y > 27 && x < 309 && y < 197) {
                draw_pixel(x + 5, y, VC_WHITE);
            }
        }

    }

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