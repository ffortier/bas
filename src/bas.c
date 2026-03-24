#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
#include <slog.h>

#include "lexer.h"
#include "parser.h"
#include "array.h"
#include "listing.h"
#include "interpreter.h"

static void logging_int(int argc, char** argv) {
    slog_init(argc > 0 ? argv[0] : "bas", SLOG_FLAGS_ALL, 0);
   
    slog_config_t cfg;
    slog_config_get(&cfg);
    cfg.nFlush = 1;
    slog_config_set(&cfg);
}

int main(int argc, char** argv) {
    logging_int(argc, argv);

    lexer_t lexer = {0};
    listing_t listing = {0};
    interpreter_state_t state = {0};

    char line[256];

    int num = 0;

    do {
        if (num != 0) {
            printf("> %d ", num);
        } else {
            printf("> ");
        }

        fgets(line, sizeof(line), stdin);

        lexer_init(&lexer, line);
        parser_t parser = {
            .lexer = &lexer,
            .error = false,
            .error_msg = {0},
            .alloc = malloc,
            .free = free,
        };
        line_t* line = parse_line(&parser, num);

        if (parser.error) {
            printf("%s\n", parser.error_msg);
            return 1;
        }

        if (line == NULL) return 1;

        if (line->statements.count > 0 && line->num != 0) {
            listing_push(&listing, line);
            num = line->num + 10;
        } else {
            num = 0;

            interpret_line(&state, &listing, line);
        }
    } while (true);
}
