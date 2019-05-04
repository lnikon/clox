#include "debug.h"

static int simpleInstruction(const char* name, int offset)
{
  printf("%s\n", name);

  return offset + 1;
}

static int constantInstruction(const char* name, Chunk* chunk, int offset)
{
  uint8_t constant = chunk->code[offset + 1];
  printf("%-16s %4d '", name, constant);
  printValue(chunk->constants.values[constant]);
  printf("'\n");
  return offset + 2;
}

void disassembleChunk(Chunk* chunk, const char* name)
{
  printf("== %s == \n", name);

  int count = 0;
  for(int offset = 0; offset < chunk->count;)
  {
    chunk->rle.count = count;
    offset = disassembleInstruction(chunk, offset);
    ++count;
  }

  int* lines = chunk->rle.lines;
  int capacity = chunk->rle.capacity;
  for(int i = 0; i < capacity; i++) {
    printf("%d", lines[i]);
  }
}

int disassembleInstruction(Chunk* chunk, int offset)
{
  printf("%04d ", offset);
  uint8_t instruction = chunk->code[offset];
  printf("%4d ", getLine(&chunk->rle, chunk->rle.count));

  switch(instruction)
  {
    case OP_RETURN:
      return simpleInstruction("OP_RETURN", offset);
    case OP_CONSTANT:
      return constantInstruction("OP_CONSTANT", chunk, offset);
    default:
      printf("Unkown instruction %d\n", instruction);
      return offset + 1;
  }
}

