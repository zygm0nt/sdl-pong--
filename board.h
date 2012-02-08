#ifndef _BOARD_H_
#define _BOARD_H_

#include <SDL.h>
extern "C" {
#include "SDL_prim.h"
}
#include "utils.h"
#include "defs.h"

namespace sdlpong {
    class brick {
        public:
            int color;
            int x, y;
            int width, height;
    };

    class board {
        private:
            int gameboard[5][10];

        public: 
            board(char * );

            void draw(SDL_Surface *view); 
            int getVal(int y, int x);
            void modVal(int y, int x, int mod);
        private:
            void draw_rect(SDL_Surface *t, brick l);
            void load_level_from_file(char *lvl_name);
    };
};

#endif
