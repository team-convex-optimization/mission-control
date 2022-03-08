#include "event_handler.h"

void shutdown(void) {
    system("sh scripts/shutdown.sh");
}

void handle_rise_event(const int pin) {
    switch (pin)
    {
    case 73: 
        /* code */
        break;
    case 138:
        break;
    case 140:
        break;
    case 7:
        break; 
    case 8:
        shutdown();
        break;
    default:
        break;
    }
}

void handle_fall_event(const int pin) {
    switch (pin)
    {
    case 73: 
        /* code */
        break;
    case 138:
        break;
    case 140:
        break;
    case 7:
        break; 
    case 8:
        shutdown();
        break;
    default:
        break;
    }
}

void handle_event(const int pin, struct gpiod_line_event *event) {

    switch (event->event_type)
    {
    case GPIOD_LINE_EVENT_RISING_EDGE:
        handle_rise_event(pin);
        break;
    case GPIOD_LINE_EVENT_FALLING_EDGE:
        handle_fall_event(pin);
        break;
    default:

        break;
    }
    return;
}

