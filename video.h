#ifndef VIDEO_H
#define VIDEO_H

#include <SDL.h>
#include <iostream>
#include <vector>
#include "SDL_prim.h"
#include "draw_container.h"

#include "load_png.h"

#define DEF_X 300
#define DEF_Y 300

namespace sdlpong {

    class video {

        private:
            SDL_Surface *window;

            int x, y;
        public:
            video();
            ~video();

            video(int x, int y);
            void set_video_mode(int x, int y);

            void refresh(void);
            void clear(void);
            void refresh(std::vector<draw_container> t);
//            void draw(std::vector<draw_container> t);

            SDL_Surface * getScreen(void);

            void end();

        private:
            void draw_led(bool on, int px, int py);
    };
};
#endif
