#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>

#include "lexer.h"

int main() {
    lexer_t lexer = {0};
    token_t tok = {0};
    char line[100];

    do {
        printf("> ");
        fgets(line, sizeof(line), stdin);

        lexer_init(&lexer, line);

        while (lexer_next(&lexer, &tok)) {
            printf("%.*s\n", (int)(tok.end - tok.begin), tok.begin);
        }
    } while (true);
}
