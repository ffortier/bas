#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>

#define STR_FMT "%.*s"
#define STR_ARG(s) (int)((s).end - (s).begin), (s).begin
#define STR_ARGP(s) (int)((s)->end - (s)->begin), (s)->begin

#define LEXER_FMT "%.*s\n%*s^"
#define LEXER_ARGP(s) (int)(lexer_eol(s) - (s)->bol), (s)->bol, (int)((s)->cur - (s)->bol), ""

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
    location_t location;
    const char* begin;
    const char* end;
} token_t;

typedef struct {
    const char* begin;
    const char* end;
    const char* cur;
    const char* bol;
    size_t line;
} lexer_t;

const char* lexer_eol(lexer_t* lexer);
void lexer_init(lexer_t* lexer, const char* input);
bool lexer_next(lexer_t* lexer, token_t* token);
bool lexer_peek(lexer_t lexer, token_t* token);

#endif
