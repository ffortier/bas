#ifndef LISTING_H
#define LISTING_H

#include "parser.h"

typedef struct {
    size_t count;
    size_t capacity;
    line_t** items;
} listing_t;

void listing_push(listing_t* listing, line_t* line);

#endif
