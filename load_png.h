#ifndef PNG_LOAD_H
#define PNG_LOAD_H

#include <SDL.h>
#include <png.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif
	
void png_read_data(png_structp ctx, png_bytep area, png_size_t size);
SDL_Surface *read_png(char *name);
/*
	png = read_png("plik.png");
*/	

#ifdef __cplusplus
}
#endif

#endif
