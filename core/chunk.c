#include "chunk.h"
#include "memory.h"
#include "value.h"
#include <stdint.h>
#include <stdlib.h>

void initChunk(Chunk *chunk) {
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = NULL;
  chunk->line = NULL;
  initValueArray(&chunk->constants);
}

void writeChunk(Chunk *chunk, uint8_t byte, int line) {
  if (chunk->capacity < chunk->count + 1) {
    int oldCapacity = chunk->capacity;
    chunk->capacity = GROW_CAPACITY(oldCapacity);
    chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
    chunk->line = GROW_ARRAY(int, chunk->line, oldCapacity, chunk->capacity);
  }

  chunk->code[chunk->count] = byte;  // Store bytecode
  chunk->line[chunk->count] = line;  // Store line number
  chunk->count++;
}

int addConstant(Chunk *chunk, Value value) {
  writeValueArray(&chunk->constants, value);
  return chunk->constants.count - 1;  // Return the index of the new constant
}

void freeChunk(Chunk *chunk) {
  FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
  FREE_ARRAY(int, chunk->line, chunk->capacity);
  freeValueArray(&chunk->constants);
  initChunk(chunk);
}
