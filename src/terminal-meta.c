#include "terminal-meta.h"

#include <stdint.h>
#include <sys/ioctl.h>

static struct winsize w;

static void update() {
    // Get terminal dimensions (and other stuff).
    ioctl(0, TIOCGWINSZ, &w);
}

uint32_t terminal_width() {
    update();
    return w.ws_row;
}

uint32_t terminal_height() {
    update();
    return w.ws_col;
}
