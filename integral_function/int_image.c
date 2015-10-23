# include <stdlib.h>
# include <stdlib.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <err.h>
# include <SDL.h>
# include "integral_function.h"
static inline
Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y) {
  int bpp = surf->format->BytesPerPixel;
  return (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
}
 
Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y) {
  Uint8 *p = pixelref(surface, x, y);
  switch(surface->format->BytesPerPixel) {
  case 1:
    return *p;
  case 2:
    return *(Uint16 *)p;
  case 3:
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
      return p[0] << 16 | p[1] << 8 | p[2];
    else
      return p[0] | p[1] << 8 | p[2] << 16;
  case 4:
    return *(Uint32 *)p;
  }
  return 0;
}
 
void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel) {
  Uint8 *p = pixelref(surface, x, y);
  switch(surface->format->BytesPerPixel) {
  case 1:
    *p = pixel;
    break;
  case 2:
    *(Uint16 *)p = pixel;
    break;
  case 3:
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
      p[0] = (pixel >> 16) & 0xff;
      p[1] = (pixel >> 8) & 0xff;
      p[2] = pixel & 0xff;
    } else {
      p[0] = pixel & 0xff;
      p[1] = (pixel >> 8) & 0xff;
      p[2] = (pixel >> 16) & 0xff;
    }
    break;
  case 4:
    *(Uint32 *)p = pixel;
    break;
  }
}

void init_sdl(void) {
  // Init only the video part
  if( SDL_Init(SDL_INIT_VIDEO)==-1 ) {
    // If it fails, die with an error message
    errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
  }
  // We don't really need a function for that ...
}

SDL_Surface* load_image(char *path) {
  SDL_Surface          *img;
  // Load an image using SDL_image with format detection
  img = IMG_Load(path);
  if (!img)
    // If it fails, die with an error message
    errx(3, "can't load %s: %s", path, IMG_GetError());
  return img;
}

Uint8 get_pixel_value(SDL_Surface *img,int x,int y){
  Uint8 r,b=0;
  SDL_GetRGB(getpixel(img,x,y),img->format,&r,&b,&b);
  return r;
}
unsigned long** int_image(SDL_Surface *img){
  unsigned long newpixel;
  unsigned long* values = calloc(img->h*img->w,sizeof(unsigned long));
  unsigned long** arr = malloc(img->w*sizeof(unsigned long*));
  for (int i=0;i<img->w;++i){
    arr[i]= values + i*img->h;
  }
  for(int i=0;i<img->w;i++){
    for(int j=0;j<img->h;j++){
      if(i-1<0){
	if(j-1<0)
	  newpixel = get_pixel_value(img,i,j);
	else
	  newpixel = get_pixel_value(img,i,j)+arr[i][j-1];
      }
      else if(j-1<0)
	newpixel =get_pixel_value(img,i,j)+arr[i-1][j];
      else
	newpixel =get_pixel_value(img,i,j)+arr[i][j-1]+arr[i-1][j]-arr[i-1][j-1];
      arr[i][j]=newpixel;
    }
  }
  return arr;
}

unsigned long sumImagePart(unsigned long** integralImage,int x1,int y1,int x2, int y2){
  int sum = integralImage[x2][y2];
  if((x1-1>=0) & (y1-1>=0))
    sum = sum - integralImage[x1-1][y2] - integralImage[x2][y1-1]+ integralImage[x1-1][y1-1];
  else if((x1-1>=0) & (y1-1<0))
    sum = sum - integralImage[x1-1][y2];
  else if((y1-1>=0) & (x1-1<0))
    sum = sum - integralImage[x2][y1-1];
  return sum;
}

int main (int argc, char *argv[]){
  if(argc<2)
    return 1;
  init_sdl();
  SDL_Surface * img=load_image(argv[1]);
    for(int i=0;i<7;i++){
      for(int j=0;j<7;j++){
	printf("%d |",get_pixel_value(img,j,i));// j,i
      }
      printf("\n");
    }
    printf("\n");
    unsigned long** integral= int_image(img);
  for(int i=0;i<7;i++){
    for(int j=0;j<7;j++){
      printf("%ld |",integral[j][i]);//j,i exactly  the same system of coordinates
    }
    printf("\n");
  }
  printf("\n Voici la somme comprise entre (0,0) et (4,4) \%ld",sumImagePart(integral,1,0,3,2));
  free(*integral);
  free(integral);
  return 0;
}



