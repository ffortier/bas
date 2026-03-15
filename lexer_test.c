#include <stdio.h>
#include <assert.h>

#include "lexer.h"

int main() {
    lexer_t lexer;
    
    lexer_init(&lexer, "\"hello\",chr$(45+69);");

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
    };

    size_t i = 0;
    token_t token = {0};

    while (lexer_next(&lexer, &token)) {
        printf("%s == %.*s\n", expected_strings[i], (int)(token.end - token.begin), token.begin);
        assert(strncmp(expected_strings[i++], token.begin, token.end - token.begin) == 0);
    }

    assert(i == sizeof(expected_strings)/sizeof(expected_strings[0]));
}
