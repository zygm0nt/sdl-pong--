#ifndef _UTILS_H_
#define _UTILS_H_

#include <SDL.h>

namespace sdlpong {

    void blend_image(SDL_Surface *view, SDL_Surface *in, SDL_Surface *to, int coeh, int mode);
    void zero_surface(SDL_Surface *view);
    void Slock(SDL_Surface *screen);
    void Sunlock(SDL_Surface *screen);

    SDL_Rect *getFrameRect(int w, int h, int x, int y);
    SDL_Surface *getSurface(SDL_Surface *, int, int);
};

#endif
