# ifndef _PREPROCESSING_H_
# define _PREPROCESSING_H_

void init_sdl(void);

SDL_Surface* load_image(char *path);
void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);
Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);
void normalized(SDL_Surface *img);
void to_grey_lvl(SDL_Surface *img);
# endif 
