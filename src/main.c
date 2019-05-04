#include "common.h"
#include "chunk.h"
#include "memory.h"
#include "debug.h"

int main(int argc, char *argv[])
{
  Chunk chunk;
  initChunk(&chunk);

  int constant = addConstant(&chunk, 123.12);
  writeChunk(&chunk, OP_CONSTANT, 1);
  writeChunk(&chunk, constant, 1);

  constant = addConstant(&chunk, -4.5);
  writeChunk(&chunk, OP_CONSTANT, 2);
  writeChunk(&chunk, constant, 2);

  constant = addConstant(&chunk, -4.5);
  writeChunk(&chunk, OP_CONSTANT, 2);
  writeChunk(&chunk, constant, 2);

  constant = addConstant(&chunk, -4.5);
  writeChunk(&chunk, OP_CONSTANT, 2);
  writeChunk(&chunk, constant, 2);

  writeChunk(&chunk, OP_RETURN, 2);

  constant = addConstant(&chunk, -4.5);
  writeChunk(&chunk, OP_CONSTANT, 2);
  writeChunk(&chunk, constant, 2);

  writeChunk(&chunk, OP_RETURN, 2);

  constant = addConstant(&chunk, -4.5);
  writeChunk(&chunk, OP_CONSTANT, 3);
  writeChunk(&chunk, constant, 3);

  writeChunk(&chunk, OP_RETURN, 3);

  disassembleChunk(&chunk, "hey ho");
  freeChunk(&chunk);
  return 0;
}

