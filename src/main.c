#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define _POSIX_C_SOURCE = 199309L
    #include <time.h>
#undef _POSIX_C_SOURCE

#include "help.h"
#include "linked-list.h"
#include "terminal-meta.h"

#define COLOUR 197
#define MAX_WIDTH 100
uint8_t width;

/*
 * Given it's current value and those of its neighbours, calculate the new value
 * of a cell.
 a*/
uint8_t calculate_value(uint8_t a, uint8_t b, uint8_t c) {
    /*
     * See https://en.wikipedia.org/wiki/Rule_110#Definition for an idea of what
     * this block does.
     */
    if (b == 1) {
        if (a == 1) {
            return !c;
        } else {
            return 1;
        }
    } else {
        return c;
    }
}

/*
 * Prints the given row, followed by a line feed.
 */
void print_row(ListItemU8* row) {
    for (uint32_t i = 0; i < width; i++) {
        // If the cell colour needs to change.
        if (i == 0 || row[i].value != row[i - 1].value) {
            if (row[i].value) {
                printf("\033[48;5;%dm", COLOUR);
            } else {
                printf("\033[0m");
            }
        }
        printf("  ");
    }
    printf("\033[0m\n");
}

void iterate(ListItemU8 row[]) {
    uint8_t first_value;
    uint8_t prev_value;
    ListItemU8* current = &row[0];

    for (uint32_t i = 0; i < width; i++) {
        uint8_t new_value = calculate_value(
            current->prev->value,
            current->value,
            current->next->value
        );
        if (i >= 2) {
            current->prev->value = prev_value;
        } else if (i == 0) {
            first_value = new_value;
        }
        prev_value = new_value;
        current = current->next;
    }

    current->prev->value = prev_value;
    current->value = first_value;
}

int main(int argc, char* argv[]) {
    // Check for at least one argument.
    if (argc < 2) {
        printf("error: no arguments\n");
        printf("See '%s -h' for help.\n", argv[0]);
        return 1;
    }

    // Check for help flag.
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        show_help();
        return 0;
    }

    // Determine width based on terminal width.
    width = terminal_width();
    if (width > MAX_WIDTH) width = MAX_WIDTH;

    // Create container array.
    ListItemU8 row[width];

    // Create blank doubly-linked list loop.
    for (uint32_t i = 0; i < width; i++) {
        row[i] = ListItemU8_new(0);
        row[i].prev = &row[i - 1];
        row[i].next = &row[i + 1];
    }
    row[0].prev = &row[width - 1];
    row[width - 1].next = &row[0];

    // Fill the loop with any valid values given from the command line.
    for (uint32_t i = 0; i < width && argv[1][i] != '\0'; i++) {
        row[i].value = argv[1][i] >= '1';
    }

    // Time delay on loop.
    struct timespec loop_delay;
    loop_delay.tv_sec = 0;
    loop_delay.tv_nsec = 50 * 1000 * 1000;

    // Loop the loop.
    while (1) {
        print_row(row);
        iterate(row);
        nanosleep(&loop_delay, NULL);
    }

    return 0;
}
