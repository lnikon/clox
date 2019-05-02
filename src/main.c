#include "common.h"
#include "chunk.h"
#include "memory.h"
#include "debug.h"

int main(int argc, char *argv[])
{
  Chunk chunk;
  initChunk(&chunk);
  writeChunk(&chunk, OP_RETURN);
  disassembleChunk(&chunk, "hey ho");
  freeChunk(&chunk);
  return 0;
}
