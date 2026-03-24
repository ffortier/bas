#include <stdio.h>
#include <assert.h>
#include <slog.h>
#include <minunit.h>

#include "lexer.h"

MU_TEST(lex) {
    lexer_t lexer;
    
    lexer_init(&lexer, "\"hello\",chr$(45+69);42");

    char *expected_strings[] = {
        "hello",
        ",",
        "chr$",
        "(",
        "45",
        "+",
        "69",
        ")",
        ";",
        "42",
    };

    size_t i = 0;
    token_t token = {0};

    while (lexer_next(&lexer, &token)) {
        slogt("%s == " STR_FMT, expected_strings[i], STR_ARG(token));
        mu_check(strncmp(expected_strings[i++], token.begin, token.end - token.begin) == 0);
    }

    mu_check(i == sizeof(expected_strings)/sizeof(expected_strings[0]));
}

MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST(lex);
}

#include "test_main.c"
