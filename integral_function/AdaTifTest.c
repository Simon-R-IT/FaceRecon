# include <stdlib.h>
# include <stdio.h>
# include <err.h>
# include <assert.h>

typedef struct
{
  unsigned long f, i, j, w, h;
  long rst;
} feature;

feature* results = haar_features(img);

unsigned long find_threshold(feature *result, unsigned long feat, unsigned long begin, unsigned long size)
{
  unsigned long pos, neg, spos, sneg, err = 0;
  for (unsigned long  i = begin; i < size - begin; i++)
  {
    if (result[i].rst <= 0)
      neg += result[i].rst;
    else
      pos += result[i].rst;
  }
  for (unsigned long j = begin; j < size - begin; j++)
  {
    if (result[i].rst < neg && result[i].rst < 0)
      sneg += result[i].rst;
    if (result[i].rst < pos && result[i].rst > 0)
      spos += result[i].rst;
  }
  if ((spos + neg - sneg) <= (sneg + pos - spos))
    err = spos + neg - sneg;
  else
    err = sneg + pos - spos;
  
}

void normalize_weight(feature* results)
{
  unsigned long index, size = 0;
  for (unsigned long i = 1; i < 6; i++)
  {
    while (result.f == i)
      size++;
    find_threshold(result, i, index, size);
    index = size;
  } 
}

