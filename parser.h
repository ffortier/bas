#ifndef AST_H
#define AST_H

#include <stddef.h>
#include <stdbool.h>

typedef struct {
} expr_t;

typedef enum {
    STMT_KIND_PRINT,
    STMT_KIND_FOR,
    STMT_KIND_IF,
    STMT_KIND_GOTO,
    STMT_KIND_GOSUB,
    STMT_KIND_NEXT,
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
    print_item_t* items;
} print_stmt_t;

typedef struct {
    stmt_kind_t kind;
    union {
        print_stmt_t print_stmt;
    } as;
} stmt_t;

#endif
