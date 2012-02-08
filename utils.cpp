#include "utils.h"
#include <iostream>
namespace sdlpong {
    void
        blend_image(SDL_Surface *view, SDL_Surface *from, SDL_Surface *to, int coeh, int mode)
        {
            int i;
            Uint8 *t;
            Uint8 *b;
            Uint8 *a;

            t = (Uint8 *)view->pixels;
            b = (Uint8 *)from->pixels;
            a = (Uint8 *)to->pixels;

            for (i=0; i < 4*(view->w*view->h); i++) {
                if (mode == 1)
                    t[i] = a[i] + ((0 - a[i])*coeh>>8);
                else	
                    t[i] = b[i]*coeh>>8;
                //t[i] = b[i] + ((a[i] - b[i])*coeh>>8);
            }
        }

    void
        zero_surface(SDL_Surface *view)
        {
            SDL_FillRect(view, NULL, SDL_MapRGB(view->format, 0,0,0));
        }

    void 
        Slock(SDL_Surface *screen)
        {
            if(SDL_MUSTLOCK(screen))
            {
                if (SDL_LockSurface(screen) < 0)
                    return;
            }
        }

    void
        Sunlock(SDL_Surface *screen)
        {
            if(SDL_MUSTLOCK(screen))
                SDL_UnlockSurface(screen);
        }

    SDL_Rect *
        getFrameRect(int w, int h, int x, int y) {
            SDL_Rect *t;
            t = new SDL_Rect;
            t->w = w;
            t->h = h;
            t->x = x;
            t->y = y;

            return t;
        }

    SDL_Surface *
        getSurface(SDL_Surface *tmpl, int w, int h) {
            SDL_PixelFormat *pxf = tmpl->format;
            return SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, pxf->BitsPerPixel, pxf->Rmask, pxf->Gmask, pxf->Bmask, pxf->Amask);
        }
};
