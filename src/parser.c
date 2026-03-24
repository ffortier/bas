#include "parser.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <slog.h>

#include "array.h"

#define CHECK_ERR(parser) do { if (parser->error) goto err; } while(0)
#define ZALLOC(t) memset(parser->alloc(sizeof(t)), 0, sizeof(t))

static bool parse_token(parser_t* parser, token_t* token, token_type_t type) {
    if (lexer_peek(*parser->lexer, token) && token->type == type) {
        return lexer_next(parser->lexer, token);
    }

    return false;
}

// static bool expect_token(parser_t* parser, token_t* token, token_type_t type) {
//     if (parse_token(parser, token, type)) {
//         return true;
//     }
// 
//     parser->error = true;
//     size_t offset = snprintf(parser->error_msg, ERROR_MSG_LEN, "Unexpected token at %d, expected %d\n", token->type, type);
//     snprintf(parser->error_msg + offset, ERROR_MSG_LEN - offset, LEXER_FMT "\n", LEXER_ARGP(parser->lexer)); 
//     return false;
// }

static bool try_parse_i32(parser_t* parser, uint32_t* out_value) {
    token_t token;

    if (!parse_token(parser, &token, TOKEN_TYPE_NUM_LIT)) {
        return false;
    }

    // TODO: Check overflow, negative numbers, floating points
    uint32_t val = 0;
    char const* begin = token.begin;

    while (begin != token.end) {
        val *= 10;
        val += *begin - '0';
        begin += 1;
    }

    *out_value =  val;
    return true;
}

static stmt_t* parse_print_stmt(parser_t* parser) {
slogt("parse_print_stmt");
    stmt_t* stmt = ZALLOC(stmt_t);

    stmt->kind = STMT_KIND_PRINT;
    stmt->as.print_stmt = ZALLOC(print_stmt_t);
    
    print_item_t* item = ZALLOC(print_item_t);

    item->kind = PRINT_ITEM_KIND_EXPR;
    item->expr = ZALLOC(expr_t);
    item->expr->kind = EXPR_KIND_STR_LIT;
    item->expr->as.str = "hello world";
    
    array_push(stmt->as.print_stmt, item);
    return stmt;
}

static stmt_t* parse_goto_stmt(parser_t* parser) {
    stmt_t* stmt = parser->alloc(sizeof(stmt_t));
    memset(stmt, 0, sizeof(stmt_t));
    stmt->kind = STMT_KIND_GOTO;
    stmt->as.goto_stmt->line_num = 10;

    return stmt;
}

static stmt_t* parse_statement(parser_t* parser) {
    token_t token = {0};
    if (!parse_token(parser, &token, TOKEN_TYPE_IDENT)) {
        slogt("no ident");
        return NULL;
    }

    slogt("ident: " STR_FMT, STR_ARG(token));

    if (strncmp(token.begin, "print", 5) == 0) {
        return parse_print_stmt(parser);
    }

    if (strncmp(token.begin, "goto", 4) == 0) {
        return parse_goto_stmt(parser);
    }

    parser->error = true;
    snprintf(parser->error_msg, ERROR_MSG_LEN, "Unknown statement identifier %.*s", (int)(token.end - token.begin), token.begin);

    return NULL;
}

line_t* parse_line(parser_t* parser, size_t default_num) {
    slogt("parse_line");
    line_t* line = parser->alloc(sizeof(line_t));

    memset(line, 0, sizeof(line_t));

    slogt("trying to parse line num");

    if (!try_parse_i32(parser, &line->num)) {
        slogt("no line num found, using %zu", default_num);
        line->num = default_num;
    }
    CHECK_ERR(parser);
    stmt_t* stmt;

    while ((stmt = parse_statement(parser)) != NULL) {
        array_push(&line->statements, stmt);
    }
    CHECK_ERR(parser);

    return line;
err:

    parser->free(line);
    return NULL;
}

void parser_report_error(FILE* stderr);

