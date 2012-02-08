#ifndef _STICK_H_
#define _STICK_H_

#include <SDL.h>
extern "C" {
#include "SDL_prim.h"
}
#include "utils.h"
#include "defs.h"

namespace sdlpong {
    class stick {
private:
        int x_cord, y_cord;
        int color;

public:
        stick();
        stick(int);
        void setCords(int, int);
        void draw(SDL_Surface *view);
    };
};

#endif
