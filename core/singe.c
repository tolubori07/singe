#include "vm.h"
#include <cstdio>
#include <stdatomic.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void repl() {
  char line[1024];
  for (;;) {
    printf(">");
    if (!fgets(line, sizeof(line), stdin)) {
      printf("\n");
      break;
    }
    interprete(line);
  }
}

static char *readFile(const char *path) {
  FILE *file = fopen(path, "rb");
  if (file == NULL) {
    fprintf(stderr, "Could not open file \"%s\".\n", path);
    exit(74);
  }

  fseek(file, 0L, SEEK_END);
  size_t filesize = ftell(file);
  rewind(file);

  char *buffer = (char *)malloc(filesize + 1);
  if (buffer == NULL) {
    fprintf(stderr, "Not enough memory to read \"%s\".\n", path);
    exit(74);
  }
  size_t bytesRead = fread(buffer, sizeof(char), filesize, file);
  if (bytesRead < filesize) {
    fprintf(stderr, "Couldn't read file \"%s\". \n", path);
    exit(74);
  }
  buffer[bytesRead] = '\0';

  fclose(file);
  return buffer;
}

static void runFile(const char *path) {
  char *source = readFile(path);
  InterpretResult result = interprete(source);
  free(source);

  if (result == INTERPRET_COMPILE_ERROR)
    exit(65);
  if (result == INTERPRET_RUNTIME_ERROR)
    exit(70);
}

int main(int argc, char *argv[]) {

  initVM();
  if (argc == 1) {
    repl();
  } else if (argc == 2) {
    runFile(argv[1]);
  } else {
    fprintf(stderr, "Usage: clox [path] \n");
    exit(64);
  }

  // Chunk chunk;
  /*
   initChunk(&chunk);
  int constant = addConstant(&chunk, 1.2);
  writeChunk(&chunk, Op_constant, 123);
  writeChunk(&chunk, constant, 123);
  constant = addConstant(&chunk, 3.4);
  writeChunk(&chunk, Op_constant, 123);
  writeChunk(&chunk, constant, 123);

  writeChunk(&chunk, Op_Add, 123);

  constant = addConstant(&chunk, 5.6);
  writeChunk(&chunk, Op_constant, 123);
  writeChunk(&chunk, constant, 123);

  writeChunk(&chunk, Op_Divide, 123);
  writeChunk(&chunk, Op_Negate, 123);
  writeChunk(&chunk, Op_return, 123);
  disassembleChunk(&chunk, "Test Chunk");
  interprete(&chunk);
*/
  freeVM();
  // freeChunk(&chunk);
  return EXIT_SUCCESS;
}
