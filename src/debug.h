#ifndef clox_debug_h
#define clox_debug_h

#include <stdio.h>
#include "chunk.h"

void disassembleChunk(Chunk* chunk, const char* name);

int disassembleInstruction(Chunk* chunk, int offset);

void printInstructionName(uint8_t byte);

#endif
