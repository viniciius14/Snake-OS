#include "utils.h"
#include "screen.h"

uint8_t *buffer = (uint8_t *)0xA0000;

/*

Port 0x3C8, 0x3C9 and 0x3C7 control the DAC. Each register in the DAC consists of 18 bits, 6 bits for each color component. To write a color, write the color index to port 0x3C8, then write 3 bytes to 0x3C9 in the order red, green, blue. If you want to write multiple consecutive DAC entries, you only need to write the first entry's index to 0x3C8 then write all values to 0x3C9 in the order red, green, blue, red, green, blue, and so on. The accessed DAC entry will automatically increment after every three bytes written. To read the DAC entries, write the index to be read to 0x3C7, then read the bytes from port 0x3C9 in a similar fashion (as with writing, the index will increment after every three bytes read) 

*/
#define PALETTE_MASK 0x3C6
#define PALETTE_READ 0x3C7
#define PALETTE_WRITE 0x3C8
#define PALETTE_DATA 0x3C9
void init_screen(void) {
    // mode_video();
    // outportb(0x3C8, 0); // color index
    // configure palette with 8-bit RRRGGGBB color
    outportb(PALETTE_MASK, 0xFF);
    outportb(PALETTE_WRITE, 0);
    for (uint8_t i = 0; i < 255; i++) {
        outportb(PALETTE_DATA, (((i >> 5) & 0x7) * (256 / 8)) / 4);
        outportb(PALETTE_DATA, (((i >> 2) & 0x7) * (256 / 8)) / 4);
        outportb(PALETTE_DATA, (((i >> 0) & 0x3) * (256 / 4)) / 4);
    }

    // set color 255 = white
    outportb(PALETTE_DATA, 0x3F);
    outportb(PALETTE_DATA, 0x3F);
    outportb(PALETTE_DATA, 0x3F);
}


/* change from text mode to video mode*/
void mode_video(void) {
    __asm__ __volatile__("movw $0x000D, %ax;");
    __asm__ __volatile__("int $0x10;");

}


