#include "debug.h"

static int simpleInstruction(const char* name, int offset)
{
  printf("name: %s\n", name);

  return offset + 1;
}

static int constantInstruction(const char* name, Chunk* chunk, int offset)
{
  uint8_t constant = chunk->code[offset + 1];
  printf("name: %-16s cnst: %4d '", name, constant);
  printValue(chunk->constants.values[constant]);
  printf("'\n");
  return offset + 2;
}

void disassembleChunk(Chunk* chunk, const char* name)
{
  printf("== name: %s == \n", name);

  for(int offset = 0; offset < chunk->count;)
  {
    offset = disassembleInstruction(chunk, offset);
  }
}

int disassembleInstruction(Chunk* chunk, int offset)
{
  printf("addr: %04d ", offset);
  uint8_t instruction = chunk->code[offset];
  printf("ln: %4d ", chunk->lines[offset]);

  switch(instruction)
  {
    case OP_CONSTANT:
      return constantInstruction("OP_CONSTANT", chunk, offset);
    case OP_ADD:
      return simpleInstruction("OP_ADD", offset);
    case OP_SUBSTRACT:
      return simpleInstruction("OP_SUBSTRACT", offset);
    case OP_MULTIPLY:
      return simpleInstruction("OP_MULTIPLY", offset);
    case OP_DIVIDE:
      return simpleInstruction("OP_DIVIDE", offset);
    case OP_NEGATE:
      return simpleInstruction("OP_NEGATE", offset);
    case OP_RETURN:
      return simpleInstruction("OP_RETURN", offset);
    default:
      printf("Unkown instruction %d\n", instruction);
      return offset + 1;
  }
}

