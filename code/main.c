#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <gpiod.h>

#include "event_handler.h"
#include "tco_libd.h"

int log_level = LOG_INFO | LOG_DEBUG | LOG_ERROR;

#define LINES_PER_CHIP 32
const int PINS[PIN_COUNT] = {73, 138, 140, 7, 0};

int main(int argc, const char *argv[]) 
{
    if (log_init("mission_control", "./log.txt") != 0)
    {
        printf("Failed to initialize the logger\n");
        return EXIT_FAILURE;
    }

    struct timespec timeout = {0, 10000000}; /* .1 second */
    struct gpio_handle_t lines[PIN_COUNT] = {};
    struct gpiod_line_event event = {};

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
    }

    log_info("Began waiting for events on switch pins");

    while (1) {
        for (int i = 0; i < PIN_COUNT; i++) {
            int ret = gpiod_line_event_wait(lines[i].line, &timeout);
            switch (ret)
            {
                case -1:
                    log_error("failed to get event on line");
                    break;
                case 1:
                    if (gpiod_line_event_read(lines[i].line, &event) < 1) {
                        log_error("failed to read event for pin %d", i);
                    }
                    handle_event(PINS[i], &event);
                default:
                    break;
            }
        }
    }

    return 0;
fail:
    return EXIT_FAILURE;
}