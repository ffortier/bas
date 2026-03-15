#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>

#include "lexer.h"

typedef struct {
    size_t count;
    size_t capacity;
    size_t item_size;
} array_t;

void* array_alloc(size_t item_size, size_t initial_capacity) {
    array_t* header = malloc(sizeof(array_t) + initial_capacity * sizeof(item_size));
    header->capacity = initial_capacity;
    header->count = 0;
    header->item_size = item_size;
    return (header + 1);
}


#define array_push(arr, item) do { \
    array_t* header = ((array_t*)arr) - 1; \
        if (header->count >= header->capacity) { \
            header = realloc(header, sizeof(array_t) + header->capacity * 2 * header->item_size); \
            assert(header != 0); \
            header->capacity *= 2; \
            arr = (void*)(header + 1); \
        } \
        \
        arr[header->count++] = item; \
    } while(0)

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
