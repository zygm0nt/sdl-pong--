#include "collision.h"

namespace sdlpong {
    int
        detect_collision(board *brd, ball *p)
        {
            int x_t, y_t;

            x_t = floor(p->getX() / (MAX_X/10)) ;

            if (x_t < 0)
                x_t = 0;
            if (p->getY() > 0.33*MAX_Y)
                return 0;
            else 
            {
                y_t = ceil((p->getY() / (0.33*MAX_Y/5)) - 1);
                if (brd->getVal(y_t, x_t) == 0)
                    return 0;
                else
                {
                    brd->modVal(y_t,x_t, -1);
                    p->setA((p->getA())*(-1));
                    return 1;
                }
            }
            return 0;
        } 
};
