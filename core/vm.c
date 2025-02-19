#include "vm.h"
#include "chunk.h"
#include "common.h"
#include "compiler.h"
#include "debug.h"
#include "value.h"
#include <_inttypes.h>
#include <stdio.h>

VM vm;
static void resetStack() { vm.stackTop = vm.stack; }
void initVM() { resetStack(); }

void freeVM() {}

void push(Value value) {
  *vm.stackTop = value;
  vm.stackTop++;
}

Value pop() {
  vm.stackTop--;
  return *vm.stackTop;
}

static InterpretResult run() {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#define BINARY_OP(op)                                                          \
  do {                                                                         \
    double b = pop();                                                          \
    double a = pop();                                                          \
    push(a op b);                                                              \
  } while (false)
  for (;;) {

#ifdef DEBUG_TRACE_EXECUTION
    printf("        ");
    for (Value *slot = vm.stack; slot < vm.stackTop; slot++) {
      printf("[");
      printValue(*slot);
      printf("]");
    }
    printf("\n");
    disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif

    uint8_t instruction;
    switch (instruction = READ_BYTE()) {
    case Op_return: {
      printValue(pop());
      printf("\n");
      return INTERPRET_OK;
    }
    case Op_constant: {
      Value constant = READ_CONSTANT();
      push(constant);
      break;
    }
    case Op_Negate:
      push(-pop());
      break;
    case Op_Add:
      BINARY_OP(+);
      break;
    case Op_Subtract:
      BINARY_OP(-);
      break;
    case Op_Multiply:
      BINARY_OP(*);
      break;
    case Op_Divide:
      BINARY_OP(/);
      break;
    }
  }
#undef READ_BYTE
#undef READ_CONSTANT
#undef BINARY_OP
}

InterpretResult interprete(const char* source){
  compile(source);
  return INTERPRET_OK;
}
