#include <stdlib.h>

#include "memory.h"
#include "rle.h"

void initRLE(RLE* rle)
{
  rle->lines = NULL;
  rle->count = 0;
  rle->capacity = 0;
  rle->opCount = -1;
}

void writeRLE(RLE* rle, int line)
{
  if(line > rle->capacity) {
    int oldCapacity = rle->capacity;
    rle->capacity = GROW_CAPACITY(oldCapacity);
    rle->lines = GROW_ARRAY(rle->lines, int, oldCapacity, rle->capacity);
  } 

  rle->lines[line]++;
  rle->count++;
}

void freeRLE(RLE* rle)
{
  FREE_ARRAY(int, rle->lines, rle->capacity);
}

int getLine(RLE* rle, int index)
{
  int sum = 0;
  int linen = 1;
  while(sum <= index && linen <= rle->capacity)
  {
    sum += rle->lines[linen++]; 
  }

  return linen - 1;
}
