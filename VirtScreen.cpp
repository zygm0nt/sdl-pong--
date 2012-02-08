#include "VirtScreen.h"
#include "utils.h"

VirtScreen::VirtScreen() {
}

VirtScreen::~VirtScreen() {
    for (std::map<std::string, SDL_Surface *>::iterator iter = _srfcs.begin(); iter != _srfcs.end(); iter++) {
        SDL_FreeSurface((*iter).second);
    }
    for (std::map<std::string, SDL_Rect *>::iterator iter = _frames.begin(); iter != _frames.end(); iter++) {
        delete (*iter).second;
    }

}

void
VirtScreen::addScreen(std::string key, SDL_Surface *surf, SDL_Rect *rect) {
    _srfcs[key] = surf;
    _frames[key] = rect;
}

SDL_Surface *
VirtScreen::getScreen(std::string key) {
    return _srfcs[key];
}

void
VirtScreen::draw(SDL_Surface *s) {

    for (std::map<std::string, SDL_Surface*>::iterator iter = _srfcs.begin(); iter != _srfcs.end(); iter++) {
        SDL_Rect *t = _frames[(*iter).first];
        SDL_BlitSurface((*iter).second, NULL, s, t);
    }
}

void
VirtScreen::draw(SDL_Surface *s, std::vector<std::string> drawable) {
    for (std::vector<std::string>::iterator iter = drawable.begin(); iter != drawable.end(); iter++) {
        SDL_BlitSurface(_srfcs[*iter], NULL, s, _frames[*iter]);
    }
}
