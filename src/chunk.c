#include <stdlib.h>

#include "chunk.h"
#include "common.h"
#include "memory.h"
#include "rle.h"

void initChunk(Chunk *chunk) {
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = NULL;

  initValueArray(&chunk->constants);
  initRLE(&chunk->rle);
}

void freeChunk(Chunk *chunk) {
  FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
  freeValueArray(&chunk->constants);
  freeRLE(&chunk->rle);

  initChunk(chunk);
  initValueArray(&chunk->constants);
  initRLE(&chunk->rle);
}

void writeChunk(Chunk *chunk, uint8_t byte, int line) {
  if(chunk->capacity < chunk->count + 1) {
    int oldCapacity = chunk->capacity;
    chunk->capacity = GROW_CAPACITY(oldCapacity);
    chunk->code = GROW_ARRAY(chunk->code, uint8_t,
        oldCapacity, chunk->capacity);
  }

  // Assume, that the first byte is instruction
  if(chunk->rle.opCount > 0) {
    chunk->rle.opCount--;
  } else {
    writeRLE(&chunk->rle, line);
    chunk->rle.opCount = operandsCount(byte);
  }

  chunk->code[chunk->count] = byte;
  chunk->count++;
}

int addConstant(Chunk* chunk, Value value) {
  writeValueArray(&chunk->constants, value);
  return chunk->constants.count - 1;
}

int operandsCount(OpCode opcode) {
  switch(opcode) {
    case OP_CONSTANT:
      return 1;
    case OP_RETURN:
      return 0;
    default:
      return -1;
  }
}
