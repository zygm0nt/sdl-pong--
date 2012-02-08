#include "video.h"

namespace sdlpong {

    using namespace std;

    video::video() {
        window = NULL;
        SDL_Init(SDL_INIT_VIDEO);
        this->x = DEF_X;
        this->y = DEF_Y;

    }

    video::~video() {

        SDL_Quit();
    }

    video::video(int x, int y) {

        window = NULL;
        SDL_Init(SDL_INIT_VIDEO);

        this->x = x;
        this->y = y;

        this->window = SDL_SetVideoMode(x, y, 0, 0);

    }

    void
        video::set_video_mode(int x, int y) {
            if (window != NULL)
                return;

            this->x = x;
            this->y = y;

            this->window = SDL_SetVideoMode(x, y, 0, 0);
        }

    void
        video::clear(void) {
            SDL_FillRect(window, NULL, SDL_MapRGB(window->format, 0, 0, 0));
        }

    void 
        video::refresh(void) {
            SDL_Flip(this->window);
        }

    void
        video::refresh(std::vector<draw_container> t) {

            SDL_FillRect(window, NULL, SDL_MapRGB(window->format, 0, 0, 0));
            for (unsigned int i = 0 ; i < t.size(); i++) {
                /*if (t[i].type == OBJ_DRONE)
                  draw_drone(t[i].x, t[i].y);
                  */
            }
            SDL_Flip(this->window);
        }

/*    void
        video::draw(std::vector<draw_container> t) {
            for (unsigned int i = 0 ; i < t.size(); i++) {
                if (t[i].type == OBJ_LED_ON)
                    draw_led(true, t[i].x, t[i].y);
                else if (t[i].type == OBJ_LED_OFF)
                    draw_led(false, t[i].x, t[i].y);
            }	
        }
*/
    void
        video::end(void) {
            SDL_Quit();
        }

    SDL_Surface *
        video::getScreen(void) {
            return window;
        }

};
