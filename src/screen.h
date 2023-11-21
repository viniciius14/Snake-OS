#ifndef SCREEN_H
#define SCREEN_H

#define SCREEN_WIDTH    320
#define SCREEN_HEIGHT   200
#define SCREEN_SIZE     SCREEN_WIDTH * SCREEN_HEIGHT

#define COLOR(_r, _g, _b)\
    ((_r & 0x3F) << 0 ) |\
    ((_g & 0x3F) << 6 ) |\
    ((_b & 0x3F) << 12)


void init_screen(void);
void mode_video(void);


#endif /* SCREEN_H */