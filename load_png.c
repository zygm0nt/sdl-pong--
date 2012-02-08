#include "load_png.h"

void png_read_data(png_structp ctx, png_bytep area, png_size_t size)
{
	SDL_RWops *src;

	src = (SDL_RWops *)png_get_io_ptr(ctx);
	SDL_RWread(src, area, size, 1);
}

SDL_Surface *
read_png(char *name) {
	SDL_RWops *src;
	SDL_Surface *surface;
	
	unsigned char header[4];
	unsigned int is_png;
	
	png_structp png_ptr;
	png_infop info_ptr;
	//png_infop end_info;
	png_bytep *row_pointers;
	int row;

	png_uint_32 png_width;
	png_uint_32 png_height;
	int bit_depth;
	int color_type;
	int interlaced_type;

	Uint32 Rmask;
	Uint32 Gmask;
	Uint32 Bmask;
	Uint32 Amask;
	
    
    printf("%s\n", name);
	src = SDL_RWFromFile(name, "rb");

	if (!src)
		printf("libpng :: error opening png file\n");
	else {
		SDL_RWread(src, header, 1, 4);
		is_png = !png_sig_cmp(header, 0, 4);
		if (!is_png)
			printf("libpng :: error - not a png file\n");
	}
	
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
			NULL, NULL, NULL);
	if (png_ptr == NULL)
		printf("libpng :: error allocating memory for png file\n");
	else {
		info_ptr = png_create_info_struct(png_ptr);
		if (info_ptr == NULL) {
			png_destroy_read_struct(&png_ptr, NULL, NULL);
			printf("libpng :: error getting info from png file\n");
		}
	}

	if (setjmp(png_ptr->jmpbuf)) {
		png_destroy_read_struct(&png_ptr, &info_ptr, 0);
		SDL_RWclose(src);
		printf("libpng :: ERROR\n");
		return NULL;
	}

	png_set_sig_bytes(png_ptr, 4);
	
	png_set_read_fn(png_ptr, src, png_read_data);
	
	png_read_info(png_ptr, info_ptr);
	png_get_IHDR(png_ptr, info_ptr, &png_width, &png_height, &bit_depth, 
			&color_type, &interlaced_type, NULL, NULL);

/*	png_set_strip_16(png_ptr);
	png_set_packing(png_ptr);
*/
	if (color_type == PNG_COLOR_TYPE_GRAY)
		png_set_expand(png_ptr);
	if (color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
		png_set_gray_to_rgb(png_ptr);

	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
		png_set_tRNS_to_alpha(png_ptr);

	if (bit_depth == 16)
		png_set_strip_16(png_ptr);
	if (bit_depth < 8)
		png_set_packing(png_ptr);
	
	png_read_update_info(png_ptr, info_ptr);
	png_get_IHDR(png_ptr, info_ptr, &png_width, &png_height, &bit_depth, 
			&color_type, &interlaced_type, NULL, NULL);
	
	if ( color_type != PNG_COLOR_TYPE_PALETTE ) {
		if ( SDL_BYTEORDER == SDL_LIL_ENDIAN ) {
			Rmask = 0x000000FF;
			Gmask = 0x0000FF00;
			Bmask = 0x00FF0000;
			Amask = (info_ptr->channels == 4) ? 0xFF000000 : 0;
		} else {
		        int s = (info_ptr->channels == 4) ? 0 : 8;
			Rmask = 0xFF000000 >> s;
			Gmask = 0x00FF0000 >> s;
			Bmask = 0x0000FF00 >> s;
			Amask = 0x000000FF >> s;
		}
	}

	surface = SDL_AllocSurface(SDL_SWSURFACE, png_width, png_height,
			bit_depth*info_ptr->channels, Rmask, Gmask, 
			Bmask, Amask);

	row_pointers = (png_bytep*) malloc(sizeof(png_bytep)*png_height);
	
	for (row = 0; row < (int)png_height; row++) {
		row_pointers[row] = (png_bytep)
				(Uint8 *)surface->pixels + row*surface->pitch;
	}

	png_read_image(png_ptr, row_pointers);

	png_read_end(png_ptr, info_ptr);
	
	png_destroy_read_struct(&png_ptr, &info_ptr, 0);
	free(row_pointers);

	return surface;
}
