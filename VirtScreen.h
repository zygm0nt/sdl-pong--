#ifndef _VIRT_SCREEN_H_
#define _VIRT_SCREEN_H_

#include <SDL.h>
#include <string>
#include <vector>
#include <iostream>
#include <map>

class VirtScreen {
    protected:
        std::map<std::string, SDL_Surface *> _srfcs;
        std::map<std::string, SDL_Rect *> _frames;

    public:
        VirtScreen();
        ~VirtScreen();

        void addScreen(std::string, SDL_Surface *, SDL_Rect *);
        SDL_Surface * getScreen(std::string);

        void draw(SDL_Surface *);
        void draw(SDL_Surface *, std::vector<std::string>);

};
#endif
