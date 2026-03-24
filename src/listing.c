#include "listing.h"
#include "array.h"

void listing_push(listing_t* listing, line_t* line) {
    array_push(listing, line);
}

