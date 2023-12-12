#include "screen.h"
#include "timer.h"

static uint8_t *video_memory = (uint8_t *)0xA0000;

void init_screen() {
    while(1) {
        for( int x  = 0 ; x != 255 ; x++) {
            for(int i = 0; i < SCREEN_SIZE; i++) {
                unsigned char *pixel = video_memory + (i / SCREEN_WIDTH) * 320 + (i % SCREEN_WIDTH);
                *pixel = x;
            }
            sleep(18);
        }

    }


}
