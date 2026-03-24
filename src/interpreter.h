#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "parser.h"
#include "listing.h"

typedef struct {
    size_t num;
} interpreter_state_t;

void interpret_next(interpreter_state_t* state, const listing_t* listing);
void interpret_stmt(interpreter_state_t* state, const listing_t* listing, const stmt_t* stmt);
void interpret_line(interpreter_state_t* state, const listing_t* listing, const line_t* line);

#endif
