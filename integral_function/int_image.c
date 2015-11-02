# include <stdlib.h>
# include <stdlib.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <err.h>
# include <SDL.h>
# include "Preprocessing.h"

Uint8 get_pixel_value(SDL_Surface *img,int x,int y){
  Uint8 r, b = 0;
  SDL_GetRGB(getpixel(img,x,y),img->format,&r,&b,&b);
  return r;
}
unsigned long** int_image(SDL_Surface *img){
  unsigned long newpixel;
  unsigned long* values = calloc(img->h*img->w,sizeof(unsigned long));
  unsigned long** arr = malloc(img->w*sizeof(unsigned long*));
  for (int i=0; i < img->w; ++i){
    arr[i]= values + i*img->h;
  }
  for(int i=0; i<img->w; i++){
    for(int j=0; j<img->h; j++){
      if(i-1 < 0){
	if(j-1 < 0)
	  newpixel = get_pixel_value(img,i,j);
	else
	  newpixel = get_pixel_value(img,i,j)+arr[i][j-1];
      }
      else if(j-1 < 0)
	newpixel = get_pixel_value(img,i,j)+arr[i-1][j];
      else
	newpixel = get_pixel_value(img,i,j)+arr[i][j-1]+arr[i-1][j]-arr[i-1][j-1];
      arr[i][j] = newpixel;
    }
  }
  return arr;
}

unsigned long sumImagePart(unsigned long** integralImage,unsigned long x1,unsigned long y1,unsigned long x2, unsigned long y2){
  x1 = x1+y1;
  y1 = x1-y1;
  x1 = x1-y1;
  x2 = x2+y2;
  y2 = x2-y2;
  x2 = x2-y2;
    
  unsigned long sum = integralImage[x2][y2];
  if((x1 >= 1) & (y1 >= 1))
    sum = sum - integralImage[x1-1][y2] - integralImage[x2][y1-1]+ integralImage[x1-1][y1-1];
  else if((x1 >= 1) & (y1 < 1))
    sum = sum - integralImage[x1-1][y2];
  else if((y1 >= 1) & (x1 < 1))
    sum = sum - integralImage[x2][y1-1];
  return sum;
}


typedef struct
{
  unsigned long f;
  unsigned long i;
  unsigned long j;
  unsigned long w;
  unsigned long h;
  long rst;
} feature;

void set_feature(feature *features, unsigned long index, unsigned long f, unsigned long i, unsigned long j, unsigned long w, unsigned long h,  long rst)
{
  features[index].f = f;
  features[index].i = i;
  features[index].j = j;
  features[index].w = w;
  features[index].h = h;
  features[index].rst = rst;
}

feature* haar_features(SDL_Surface * img)
{
  unsigned long** tab = int_image(img);
  feature *features = malloc(200000* sizeof(*features));
  unsigned long index = 0;
  unsigned long i = 0;
  unsigned long j = 0;
  unsigned long w = 1;
  unsigned long  h = 1;
  long S1 = 0;
  long S2 = 0;
  long S3 = 0;
  long S4 = 0;
  int counter = 0;
  printf("\n");
  for(i = 0;  i <= 23; i++)
  {
    for(j = 0; j <= 23; j++)
    {
       for(h=1; i+h-1 <= 23; h++)
       {
         for(w=1; j+2*w-1<24 ; w++)
	 {
           S1 = sumImagePart(tab,i, j,  i+h-1, j+w-1);
           S2 = sumImagePart(tab,i, j+w, i+h-1 , j+2*w-1);
	   //if (counter < 15)
	   //printf("a : S1 %04lu S2 %04lu Sum %04ld\n", S1, S2, S1-S2);
           set_feature(features, index, 1, i, j, w, h, S1-S2);
           index++;
	   counter++;
	 }
       }
    }
  }
  for(i = 0;  i <= 23; i++)
  {
    for(j = 0; j <= 23; j++)
    {
      for(h=1; i+h-1 <= 23; h++)
      {
	for(w=1; j+3*w-1<24 ; w++)
        {
	  S1 = sumImagePart(tab, i, j, i+h-1, j+w-1);
          S2 = sumImagePart(tab, i, j+w, i+h-1, j+2*w-1);
          S3 = sumImagePart(tab, i, j+2*w, i+h-1, j+3*w-1);
	  if (w < 15 && h == 1 && i == 0 && j == 0)
	     printf("b : S1 %04lu S2 %04lu Sum %04ld\n", S1, S2, S1-S2);
          set_feature(features, index, 2, i, j, w, h, S1-S2+S3);
          index++;
	}
      }
    }
  }
  for(i = 0;   i <= 23; i++)
  {
    for(j = 0; j <= 23;j++)
    {
      for(h=1; i+2*h-1 <= 23; h++)
      {
	for(w=1; j+w-1 <24 ; w++)
	{
	  S1 = sumImagePart(tab, i, j, i+h-1, j+w-1);
          S2 = sumImagePart(tab, i+h, j, i+2*h-1, j+w-1);
          set_feature(features, index, 3, i, j, w, h, S1-S2);
          index++;
	}
      }
    }
  }
  for(i = 0;  i <= 23; i++)
  {
    for(j = 0; j <=23;j++)
    {
      for(h = 1; i+3*h-1 <= 23; h++)
      {
	for(w = 1; j+w-1 <24 ; w++)
	{
	  S1 = sumImagePart(tab, i, j, i+h-1, j+w-1);
          S2 = sumImagePart(tab, i+h, j, i+2*h-1, j+w-1);
          S3 = sumImagePart(tab, i+2*h, j, i+3*h-1, j+w-1);
          set_feature(features, index, 4, i, j, w, h, S1-S2+S3);
	  index++;
	}
      }
    }
  }
  for(i = 0;  i <= 23; i++)
  {
    for(j = 0; j <= 23; j++)
    {
      for(h=1; i+2*h-1 <= 23; h++)
      {
	for(w=1; j+2*w-1<=23 ; w++)
	{
	  S1 = sumImagePart(tab, i, j, i+h-1, j+w-1);
          S2 = sumImagePart(tab, i+h, j, i+2*h-1, j+w-1);
          S3 = sumImagePart(tab, i, j+w, i+h-1, j+2*w-1);
          S4 = sumImagePart(tab, i+h, j+w, i+2*h-1,j+2*w-1);
          set_feature(features, index, 5, i, j, w, h, S1-S2-S3+S4);
          index++;
	}
      }
    }
  }
  printf("\n Number of Features : %lu\n",index);
  printf("Feature : %lu, %lu, %lu, %lu, %lu, %ld\n", features[1500].f, features[1500].i, features[1500].j, features[1500].w, features[1500].h, features[1500].rst); 
  return features;
}


int main (int argc, char *argv[]){
  if(argc<2)
    return 1;
  init_sdl();
  SDL_Surface * img=load_image(argv[1]);
  to_grey_lvl(img);
  normalized(img);
  for(int i=0;i<7;i++)
  {
    for(int j=0;j<7;j++)
    {
      printf("%03d |",get_pixel_value(img,j,i));// j,i
    }
    printf("\n");
  }
  printf("\n");
  unsigned long** integral= int_image(img);
  for (int i = 0; i<7; i++)
  {
    for (int j = 0; j<7; j++)
    {
      printf("%04ld |",integral[j][i]); //j,i exactly  the same system of coordinates
    }
    printf("\n");
  }
  printf("\n Voici la somme comprise entre (0,0) et (3,3) %ld\n",sumImagePart(integral,0,0,3,3));
  feature* results = haar_features(img);
  free(results);
  free(*integral);
  free(integral);
  return 0;
}
