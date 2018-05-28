#include "linked-list.h"

ListItemU8 ListItemU8_new(uint8_t value) {
    ListItemU8 list_item;

    list_item.prev = NULL;
    list_item.next = NULL;

    list_item.value = value;

    return list_item;
}
