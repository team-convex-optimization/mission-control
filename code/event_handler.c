#include "event_handler.h"

void handle_event(const int pin, struct gpiod_line_event *event) {
    
    switch (event->event_type)
    {
    case GPIOD_LINE_EVENT_RISING_EDGE:
            printf("Ron pin %d \n", pin);

        break;
    case GPIOD_LINE_EVENT_FALLING_EDGE:
    printf("F on pin %d \n", pin);

        break;
    default:
    printf("other on pin %d \n", pin);

        break;
    }
    return;
}