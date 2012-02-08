#ifndef _STARS_H_
#define _STARS_H_

#include <SDL.h>
extern "C" {
#include "SDL_prim.h"
}
#include "defs.h"

namespace sdlpong {

    class star {
        public:
        int v, x, y;
    };

    class stars {
        int n;
        private:
            struct star * starfield;

        public:
            stars(int);
            ~stars();

            void iterate_sky();
            void draw(SDL_Surface *view);
    };
};

#endif
