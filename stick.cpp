#include "stick.h"

namespace sdlpong {

    stick::stick(int c) {
        color = c;
    }
    stick::stick() {

    }

    void 
        stick::draw(SDL_Surface *view)
        {
            int i,k;

            Slock(view);

            if (x_cord == -1)
                x_cord = MAX_X / 2;

            for (i = x_cord-PAD_WIDTH; i < x_cord+PAD_WIDTH; i++)
                for (k = MAX_Y-35; k < MAX_Y-15; k++)
                    if (i > 0 && i < MAX_X)
                    {
                        if (color == 1)
                            SDL_putPixel(view, i, k, SDL_MapRGB(view->format, 0, 0, 0));
                        else
                            SDL_putPixel(view, i, k, SDL_MapRGB(view->format, 100, 100, 100));
                    }
            Sunlock(view);
        }

    void
        stick::setCords(int x, int y) {
            x_cord = x;
            y_cord = y;
        }
};
