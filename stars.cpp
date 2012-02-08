#include "stars.h"

namespace sdlpong {

    stars::stars(int n) {
        this->n = n;
        starfield = new star[n];
        /* set initial stars */
        for (int x = 0; x < n; x++)
        {
            starfield[x].v = random() % 3;
            starfield[x].x = random() % MAX_X;
            starfield[x].y = random() % MAX_Y;
        }

    }

    stars::~stars() {
        delete starfield;
    }

    void
        stars::iterate_sky() {
            for (int i=0; i<n; i++)
            {
                switch(starfield[i].v)
                {
                    case 0:
                        starfield[i].x += 1;
                        break;
                    case 1:
                        starfield[i].x += 2;
                        break;
                    case 2: 
                        starfield[i].x += 3;
                        break;
                }
                if (starfield[i].x >= MAX_X)
                {
                    starfield[i].x = 0;
                    starfield[i].y = random() % MAX_Y;
                }
                else if (starfield[i].x <= 0)
                {
                    starfield[i].x = MAX_X-1;
                    starfield[i].y = random() % MAX_Y;
                }
            }
        }

    void
        stars::draw(SDL_Surface *view) {
            int color;

            for (int i=0; i<n; i++)
            {
                if (starfield[i].v == 2)
                    color = SDL_MapRGB(view->format, 255, 255, 255);
                else if (starfield[i].v == 1)
                    color = SDL_MapRGB(view->format, 255, 255, 240);
                else if (starfield[i].v == 0)
                    color = SDL_MapRGB(view->format, 255, 255, 210);
                SDL_putPixel(view, starfield[i].x, starfield[i].y, color);
            }

        }
};

