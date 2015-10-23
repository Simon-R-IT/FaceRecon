# include <stdlib.h>
# include <stdlib.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <err.h>
# include <SDL.h>
# include <integral_fucntion.h>

void set_feature(unsigned long* tab ,int rank,  int f, int i, int j, int w, int h, int rst){
        tab[rank]=f;
        tab[rank+1]=i;
        tab[rank+2]=j;
        tab[rank+3]=w;
        tab[rank+4]=h;
        tab[rank+5]=rst;

}
unsigned long* haar_features(SDL_surface *img){
  unsigned long tab**=int_image(img);
  unsigned long *rst;
  int idx = 0;
  int w = 1;
  int h = 1;
  int S1 = 0;
  int S2 = 0;
  for(int i = 1; 1 <= i <= 24; i++){
    for(int j = 1; j <= 24){
       for(w; i+h-1 <= 24; w++){
         for(h; j+2*w-1 ; h++){
           S1 = sumImagePart(tab,i,i+h-1,j,j+w-1);
           S2 = sumImagePart(tab,i,i+h-1,j+w,j+2*w-1);
           set_feature(rst, idx, 1, i, j, w, h, S1-S2);
           idx = idx + 6;
       }
     }
   }
 }
        w=1;
        h=1;
        for(int i = 1; 1 <= i <= 24; i++){
         for(int j = 1; j <= 24){
           for(w; i+h-1 <= 24; w++){
            for(h; j+3*w-1 ; h++){
            S1 = sumImagePart(tab,i,i+h-1,j,j+w-1);
            S2 = sumImagePart(tab,i,i+h-1,j+w,j+2*w-1);
            S3 = sumImagePart(tab,i,i+h-1,j+2*w,j+3*w-1);
            set_feature(rst, idx, 2, i, j, w, h, S1-S2+S3);
            idx = idx + 6;

       }
     }
   }
 }
        w=1;
        h=1;
        for(int i = 1; 1 <= i <= 24; i++){
         for(int j = 1; j <= 24){
           for(w; i+2*h-1 <= 24; w++){
            for(h; j+w-1 ; h++){
            S1 = sumImagePart(tab,i,i+h-1,j,j+w-1);
            S2 = sumImagePart(tab,i+h,i+2*h-1,j,j+w-1);
            set_feature(rst, idx, 3, i, j, w, h, S1-S2);
            idx = idx + 6;

       }
     }
   }
 }

        w=1;
        h=1;
         for(int i = 1; 1 <= i <= 24; i++){
         for(int j = 1; j <= 24){
           for(w; i+3*h-1 <= 24; w++){
            for(h; j+w-1 ; h++){
            S1 = sumImagePart(tab,i,i+h-1,j,j+w-1);
            S2 = sumImagePart(tab,i+h,i+2*h-1,j,j+w-1);
	    S3 = sumImagePart(tab,i+2*h,i+3*h-1,j,j+w-1);
            set_feature(rst, idx, 4, i, j, w, h, S1-S2+S3);
            idx = idx + 6;

       }
     }
   }
 }

        w=1;
        h=1;
         for(int i = 1; 1 <= i <= 24; i++){
         for(int j = 1; j <= 24){
           for(w; i+2*h-1 <= 24; w++){
            for(h; j+2w-1 ; h++){
            S1 = sumImagePart(tab,i,i+h-1,j,j+w-1);
            S2 = sumImagePart(tab,i+h,i+2*h-1,j,j+w-1);
	    S3 = sumImagePart(tab,i,i+h-1,j+w,j+2*w-1);
	    S4 = sumImagePart(tab,i+h, i+2h-1,j+w,j+2*w-1);
            set_feature(rst, idx, 5, i, j, w, h, S1-S2-S3+S4);
            idx = idx + 6;

       }
     }
   }
 }
        return rst;
}

