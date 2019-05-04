#ifndef clox_rle_h
#define clox_rle_h

typedef struct {
  int* lines;
  int count;
  int capacity;
  int opCount;
} RLE;

void initRLE(RLE* rle);
void writeRLE(RLE* rle, int line);
void freeRLE(RLE* RLE);
int getLine(RLE* rle, int index);

#endif
