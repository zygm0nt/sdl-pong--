#include "FileObject.h"
#include "load_png.h"

FileObject::FileObject(std::string x) {
    data = read_png((char*)x.c_str());    
}

FileObject::~FileObject() {
    if (data != NULL)
        delete data;
}

SDL_Surface *
FileObject::getData() {
    return data;
}
