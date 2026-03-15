#include "lexer.h"

#include <string.h>
#include <ctype.h>

void lexer_init(lexer_t* lexer, const char* input) {
    lexer->begin = input;
    lexer->end = input + strlen(input);
    lexer->bol = input;
    lexer->cur = input;
    lexer->line = 1;
}

static bool lexer_read_str(lexer_t* lexer, token_t* token) {
    token->type = TOKEN_TYPE_STR_LIT;
    token->begin = ++lexer->cur;
    while (lexer->cur != lexer->end && *++lexer->cur != '"');
    if (lexer->cur == lexer->end) return false;
    token->end = lexer->cur++;
    return true;
}

static bool lexer_read_ident(lexer_t* lexer, token_t* token) {
    token->type = TOKEN_TYPE_IDENT;
    token->begin = lexer->cur;
    while(lexer->cur != lexer->end && isalnum(*++lexer->cur));
    if (*lexer->cur == '$') lexer->cur += 1;
    token->end = lexer->cur;
    return true;
}

static bool lexer_read_num(lexer_t* lexer, token_t* token) {
    token->type = TOKEN_TYPE_NUM_LIT;
    token->begin = lexer->cur;
    while(lexer->cur != lexer->end && isdigit(*++lexer->cur));
    token->end = lexer->cur;
    return true;
}

static bool lexer_read_operator(lexer_t* lexer, token_t* token) {
    token->begin = lexer->cur;

    switch (*lexer->cur) {
        case '(': token->type = TOKEN_TYPE_OPAREN; break;
        case ')': token->type = TOKEN_TYPE_CPAREN; break;
        case '+': token->type = TOKEN_TYPE_PLUS; break;
        case '-': token->type = TOKEN_TYPE_MINUS; break;
        case '*': token->type = TOKEN_TYPE_MULT; break;
        case '/': token->type = TOKEN_TYPE_DIV; break;
        case ',': token->type = TOKEN_TYPE_COMMA; break;
        case ';': token->type = TOKEN_TYPE_SEMI; break;
    }

    token->end = ++lexer->cur;
    return true;
}

bool lexer_next(lexer_t* lexer, token_t* token) {
    while (lexer->cur != lexer->end) {
        switch (*lexer->cur) {
            case ' ': case '\t': case '\r':
                lexer->cur++;
                break;
            case '\n': 
                lexer->bol = ++lexer->cur;
                lexer->line += 1;
                break;
            case '"':
                return lexer_read_str(lexer, token);
            case '(': case ')': case '+': case '-': case '*': case '/': case ',': case ';': 
                return lexer_read_operator(lexer, token);
            default:
                if (isalpha(*lexer->cur)) return lexer_read_ident(lexer, token);
                if (isdigit(*lexer->cur)) return lexer_read_num(lexer, token);
                break;
        }
    }

    return false;
}
