/*
 *
 */

#ifndef INCLUDED_LINKED_LIST
#define INCLUDED_LINKED_LIST

#include <stdint.h>

typedef struct ListItemU8_s {
    struct ListItemU8_s* prev;
    struct ListItemU8_s* next;
    uint8_t value;
} ListItemU8;

ListItemU8 ListItemU8_new(uint8_t value);

#endif
