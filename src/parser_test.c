#include "parser.h"

#include <stdlib.h>
#include <slog.h>
#include <minunit.h>

MU_TEST(test_empty_line) {
    slogt("test_empty_line");
    lexer_t lexer = {0};
    lexer_init(&lexer, "");

    parser_t parser = {0};

    parser.lexer = &lexer;
    parser.alloc = malloc;
    parser.free = free;

    line_t* line =  parse_line(&parser, 0);

    mu_check(line->num == 0);
    mu_check(line->statements.count == 0);
}

MU_TEST(test_single_stmt) {
    slogt("test_single_test");

    lexer_t lexer = {0};
    lexer_init(&lexer, "print");

    parser_t parser = {0};

    parser.lexer = &lexer;
    parser.alloc = malloc;
    parser.free = free;

    line_t* line =  parse_line(&parser, 0);

    mu_check(line->num == 0);
    mu_check(line->statements.count == 1);
}

MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST(test_empty_line);
    MU_RUN_TEST(test_single_stmt);
}

#include "test_main.c"
