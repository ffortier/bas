#include "interpreter.h"

#include <assert.h>
#include <stdbool.h>
#include <inttypes.h>

#include "parser.h"
#include "array.h"

static const char* fmt_statement_kind(stmt_kind_t kind) {
    switch (kind) {
        case STMT_KIND_PRINT: return "print";
        case STMT_KIND_GOTO: return "goto";
        case STMT_KIND_RUN: return "run";
        case STMT_KIND_LIST: return "list";
        default: assert(false && "Unreachable");
    }
}

static void do_list(const listing_t* listing) {
    array_foreach(listing, line_t*, line) {
        printf("%" PRIu32 " ", (*line)->num);
        array_foreach(&(*line)->statements, stmt_t*, stmt) {
            printf("%s:", fmt_statement_kind((*stmt)->kind));
        }
        printf("\b\n");
    }
}

void interpret_next(
        interpreter_state_t* state __attribute__((unused)), 
        const listing_t* listing __attribute__((unused))) {
}

void interpret_line(
        interpreter_state_t* state,
        const listing_t* listing,
        const line_t* line) {
    array_foreach(&line->statements, stmt_t*, stmt) {
        interpret_stmt(state, listing, *stmt);
    }
}

void interpret_stmt(
        interpreter_state_t* state __attribute__((unused)), 
        const listing_t* listing, 
        const stmt_t* stmt) {
    switch (stmt->kind) {
        case STMT_KIND_PRINT:
            break;
        case STMT_KIND_GOTO:
            break;
        case STMT_KIND_RUN:
            break;
        case STMT_KIND_LIST:
            do_list(listing);
            break;
    }
}
