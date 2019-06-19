#ifndef clox_compiler_h
#define clox_compiler_h

#include "vm.h"
#include "scanner.h"

typedef struct {
  Token current;
  Token previous;
  bool hadError;
  bool panicMode;
} Parser;

typedef enum {
  PREC_NONE,
  PREC_ASSIGNMENT,
  PREC_OR,
  PREC_AND,
  PREC_EQUALITY,
  PREC_COMPARISON,
  PREC_TERM,
  PREC_FACTOR,
  PREC_UNARY,
  PREC_CALL,
  PREC_PRIMARY
} Precedence;

typedef void (*ParseFn)();

typedef struct {
  ParseFn prefix;
  ParseFn infix;
  Precedence precedence;
} ParseRule;

bool compile(const char* source, Chunk* chunk);
Chunk* currentChunk();
void errorAt(Token* token, const char* message);
void error(const char* message);
void errorAtCurrent(const char* message);
void advance();
void consume(TokenType type, const char* message);
void emitByte(uint8_t byte);
void emitBytes(uint8_t byte1, uint8_t byte2);
void emitReturn();
void emitReturn();
uint8_t makeConstant(Value value);
void emitConstant(Value value);
void endCompiler();
void binary();
void expression();
void grouping();
void number();
void unary();
void parsePrecedence(Precedence precedence);
ParseRule* getRule(TokenType type);

#endif
