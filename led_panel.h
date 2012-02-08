#ifndef LED_PANEL_H
#define LED_PANEL_H

#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>

#include "draw_container.h"
#include "led.h"

namespace sdlpong {

    class led_panel {
        private:
            std::string cur_text;
            led **panel;
            int **text_bin;
            std::string mode;

            int x;
            int y;

            int width;
            int off_x;
            int off_y;

            int act_offset;

            bool done;

            void int2bin(int w, int *t);
        public:
            led_panel();
            led_panel(int x, int y, int width);
            virtual ~led_panel();

            std::vector<draw_container> getDrawable(void);

            void all_on(void);
            void all_off(void);
            //void scroll(void);

            void set_offset(int ox, int oy);
            void print(void);
            void set_text(char *txt);
            int lightup_text(int pos);
            int scroll(void);
            bool get_done(void);
            void draw(SDL_Surface *);
            void print_bin(void);
            void set_mode(std::string);
    };
};
#endif
