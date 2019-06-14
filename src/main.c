#include "common.h"
#include "chunk.h"
#include "memory.h"
#include "debug.h"
#include "vm.h"

int main(int argc, char *argv[])
{
  initVM();

  Chunk chunk;
  initChunk(&chunk);

  int constant = addConstant(&chunk, 12);
  writeChunk(&chunk, OP_CONSTANT, 1);
  writeChunk(&chunk, constant, 1);

  constant = addConstant(&chunk, -32);
  writeChunk(&chunk, OP_CONSTANT, 2);
  writeChunk(&chunk, constant, 2);

  writeChunk(&chunk, OP_SUBSTRACT, 3);

  writeChunk(&chunk, OP_RETURN, 3);

  /*disassembleChunk(&chunk, "hey ho");*/
  interpret(&chunk);

  freeVM();
  freeChunk(&chunk);
  return 0;
}

