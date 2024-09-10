#include "chunk.h"
#include "common.h"
#include "debug.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  Chunk chunk;
  initChunk(&chunk);
  int constant = addConstant(&chunk, 1.2);
  writeChunk(&chunk, Op_constant);
  writeChunk(&chunk, constant);
  writeChunk(&chunk, Op_return);
  disassembleChunk(&chunk, "Test Chunk");
  freeChunk(&chunk);
  return EXIT_SUCCESS;
}
