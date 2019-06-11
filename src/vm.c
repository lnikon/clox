#include "common.h"
#include "value.h"
#include "debug.h"
#include "vm.h"
#include "compile.h"

VM vm;

static void resetStack()
{
    vm.stackTop = vm.stack;
}

void initVM() 
{
    resetStack();
}

void freeVM()
{
}

InterpretResult interpret(const char* source)
{
  compile(source);

  return INTERPRET_OK;
}

InterpretResult run()
{
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])

  for(;;) {
#ifdef DEBUG_TRACE_EXECUTION
      printf("        ");
      for(Value* slot = vm.stack; slot < vm.stackTop; slot++)
      {
          printf("[");
          printValue(*slot);
          printf("]");
      }
      printf("\n");
    disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif
    int8_t instruction;
    switch(instruction = READ_BYTE()) {
      case OP_RETURN: {
                            printValue(pop()); 
                            printf("\n");
                            return INTERPRET_OK;
                      }

      case OP_CONSTANT: {
                          Value constant = READ_CONSTANT();
                          push(constant);
                          break;
                        }
    }
  }

#undef READ_BYTE
#undef READ_CONSTANT
}

void push(Value value)
{
    *vm.stackTop = value;
    vm.stackTop++;
}

Value pop()
{
    vm.stackTop--;
    return *vm.stackTop;
}
