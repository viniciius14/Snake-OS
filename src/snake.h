#ifndef SNAKE_H
#define SNAKE_H

#include "utils.h"
#include "screen.h"
#include "font.h"

#define HORZ_SQUARES 20
#define VERT_SQUARES 15


/*
- Draw background
    - Checkers 20 * 15

SCORE           BEST
|   |   |   |   |...|

- Draw score and best

- Initial snake is 3 "blocks" long
*/

void game_init(void);
void board_init(void);

#endif /* SNAKE_H */