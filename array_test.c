#define ARRAY_INITIAL_CAPACITY 2
#include "array.h"

#include <assert.h>
#include <string.h>

typedef struct {
    size_t count;
    size_t capacity;
    char* items;
} string_t;

int main() {
    string_t s = {0};

    array_push(&s, 'h');
    array_push(&s, 'e');
    array_push(&s, 'l');
    array_push(&s, 'l');
    array_push(&s, 'o');
    array_push(&s, '\0');

    assert(s.count == 6); 
    assert(strncmp("hello", s.items, 5) == 0);

    return 0;
}
