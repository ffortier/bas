#ifndef AST_H
#define AST_H

#include <stddef.h>
#include <stdbool.h>

#include "lexer.h"

typedef enum {
    EXPR_KIND_STR_LIT
} expr_kind_t;

typedef struct {
    expr_kind_t kind;
    union {
        char* str;
    } as;
} expr_t;

typedef enum {
    STMT_KIND_PRINT,
    STMT_KIND_GOTO,
    STMT_KIND_RUN,
    STMT_KIND_LIST,
} stmt_kind_t;

typedef enum {
    PRINT_ITEM_KIND_EXPR,
    PRINT_ITEM_KIND_COMMA,
    PRINT_ITEM_KIND_SEMI,
} print_item_kind_t;

typedef struct {
    print_item_kind_t kind;
    expr_t *expr;
} print_item_t;

typedef struct {
    size_t count;
    size_t capacity;
    print_item_t** items;
} print_stmt_t;

typedef struct {
    uint32_t line_num;
} goto_stmt_t;

typedef struct {
    stmt_kind_t kind;
    union {
        print_stmt_t* print_stmt;
        goto_stmt_t* goto_stmt;
    } as;
} stmt_t;

typedef struct {
    uint32_t num; // 0 means it must be executed immediatly
    struct {
        size_t count;
        size_t capacity;
        stmt_t** items;
    } statements;
} line_t;

#define ERROR_MSG_LEN 256

typedef struct {
    lexer_t* lexer;
    bool error;
    char error_msg[ERROR_MSG_LEN];

    void* (*alloc)(size_t sz);
    void (*free)(void* p);
} parser_t;

line_t* parse_line(parser_t* parser, size_t default_num);

#endif
