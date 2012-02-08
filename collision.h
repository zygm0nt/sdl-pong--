#ifndef _COLLISION_H_
#define _COLLISION_H_

#include <math.h>
#include "defs.h"
#include "board.h"
#include "ball.h"

namespace sdlpong {
//    int detect_collision(board *b, int x_ball, int y_ball, int *b, int *a);
    int detect_collision(board *b, ball *p);
};
#endif
