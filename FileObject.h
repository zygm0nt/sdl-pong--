#ifndef _FACTORY_FILE_OBJECT_H_
#define _FACTORY_FILE_OBJECT_H_

#include <SDL.h>

#include "Object.h"

class FileObject : public Object {

    SDL_Surface *data;

    public:
        FileObject() { data = NULL; };
        FileObject(std::string x);
        ~FileObject();
        SDL_Surface * getData();
};
#endif
