#include "common.h"
#include "value.h"
#include "debug.h"
#include "vm.h"

VM vm;

void initVM() 
{
}

void freeVM()
{
}

InterpretResult interpret(Chunk* chunk)
{
  vm.chunk = chunk;
  vm.ip = vm.chunk->code;

  return run();
}

InterpretResult run()
{
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])

  for(;;) {
#ifdef DEBUG_TRACE_EXECUTION
    disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif
    int8_t instruction;
    switch(instruction = READ_BYTE()) {
      case OP_RETURN: {
                        return INTERPRET_OK;
                      }
      case OP_CONSTANT: {
                          Value constant = READ_CONSTANT();
                          printValue(constant);
                          printf("\n");
                          break;
                        }
    }
  }

#undef READ_BYTE
#undef READ_CONSTANT
}