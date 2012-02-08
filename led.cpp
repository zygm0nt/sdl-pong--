#include "led.h"

#include "FileFactory.h"
#include <iostream>

namespace sdlpong {

    void led::setState(bool s) {
        state = s;
    }

    bool led::getState() {
        return state;
    }

    void led::draw(SDL_Surface *screen) {
        SDL_Rect tmp;
        tmp.x = x;
        tmp.y = y;
    
        FileFactory *fFactory = FileFactory::getFactoryInstance();

        if (state == true) {
            SDL_BlitSurface(((FileObject *)(fFactory->getObject("led_on.png")))->getData(), NULL, screen, &tmp);
        } else {
            SDL_BlitSurface(((FileObject *)(fFactory->getObject("led_off.png")))->getData(), NULL, screen, &tmp);
        }
    }

    void led::setCords(int x, int y) {
        this->x = x;
        this->y = y;
    }
};
