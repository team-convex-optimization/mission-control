#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <gpiod.h>

#include "tco_libd.h"

int log_level = LOG_INFO | LOG_DEBUG | LOG_ERROR;

#define LINES_PER_CHIP 32
#define PIN_COUNT 5
const int PINS[PIN_COUNT] = {73, 138, 140, 7, 0};

int main(int argc, const char *argv[]) 
{
    if (log_init("mission_control", "./log.txt") != 0)
    {
        printf("Failed to initialize the logger\n");
        return EXIT_FAILURE;
    }

    struct timespec timeout = {0, 0};
    struct gpio_handle_t lines[PIN_COUNT] = {};
    struct gpiod_line_bulk bulk;
    struct gpiod_line_bulk events;
    gpiod_line_bulk_init(&bulk);

    for (int i = 0; i < PIN_COUNT; i++) {
        if (gpio_handle_get(&(lines[i]), PINS[i] / LINES_PER_CHIP, GPIO_DIR_NONE, PINS[i] % LINES_PER_CHIP) != ERR_OK) {
            log_error("Failed to get line handle for pin %d", PINS[i]);
            goto fail;
        }

        const char *consumer = gpiod_line_consumer(lines[i].line);
        if (gpiod_line_request_both_edges_events(lines[i].line, consumer) != 0) {
            log_error("failed to request events on pin %d", i);
            goto fail;
        }
        gpiod_line_bulk_add(&bulk, lines[i].line);
    }

    timeout.tv_sec = 1;
    timeout.tv_nsec = 0;

    // if(gpiod_line_event_wait_bulk(&bulk, &timeout, &events) == -1)
    // {
    //     perror("gpiod_line_event_wait_bulk");
    //     goto fail;
    // }

    return 0;
fail:
    return EXIT_FAILURE;
}