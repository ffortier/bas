#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

#ifndef ARRAY_INITIAL_CAPACITY
#define ARRAY_INITIAL_CAPACITY 100
#endif

#define array_push(arr, item) do { \
        if ((arr)->count >= (arr)->capacity) { \
            (arr)->items = realloc((arr)->items, ((arr)->capacity == 0 ? ARRAY_INITIAL_CAPACITY : (arr)->capacity * 2) * sizeof(*(arr)->items)); \
            assert((arr)->items != NULL); \
        } \
        (arr)->items[(arr)->count++] = item; \
    } while(0)


#define array_foreach(arr, type, item) for ( \
        size_t __i = 0, type* item = (arr)->items; \
        __i < (arr)->count; \
        i++, item++)

#endif
