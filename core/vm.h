#ifndef singe_vm_h
#define singe_vm_h
#define STACK_MAX 256
#include "value.h"
#include "chunk.h"
#include <stdint.h>

typedef struct {
  Chunk *chunk;
  uint8_t *ip;
  Value stack[STACK_MAX];
  Value* stackTop;
} VM;

typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR
} InterpretResult;

void initVM();
void freeVM();
InterpretResult interprete(const char* source);
void push(Value value);
Value pop();
#endif // !singe_vm_h
