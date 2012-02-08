#ifndef _LED_H_
#define _LED_H_

#include "draw_container.h"

namespace sdlpong {
    class led : public draw_container {
        bool state;
        public:

            led() {state = false; };
            void setState(bool st);
            bool getState();

            void draw(SDL_Surface *screen);
            void setCords(int x, int y);
    };
};
#endif 
