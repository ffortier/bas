#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>

typedef enum {
    TOKEN_TYPE_IDENT,
    TOKEN_TYPE_STR_LIT,
    TOKEN_TYPE_NUM_LIT,
    TOKEN_TYPE_OPAREN,
    TOKEN_TYPE_CPAREN,
    TOKEN_TYPE_PLUS,
    TOKEN_TYPE_MINUS,
    TOKEN_TYPE_MULT,
    TOKEN_TYPE_DIV,
    TOKEN_TYPE_COMMA,
    TOKEN_TYPE_SEMI,
} token_type_t;

typedef struct {
    size_t offset;
    size_t line;
    size_t column;
} location_t;

typedef struct {
    token_type_t type;
    const char* begin;
    const char* end;
} token_t;

typedef struct {
    const char* begin;
    const char* end;
    char const* cur;
    char const* bol;
    size_t line;
} lexer_t;

void lexer_init(lexer_t* lexer, const char* input);
bool lexer_next(lexer_t* lexer, token_t* token);
void lexer_report_error(lexer_t* lexer, FILE* out);

#endif
