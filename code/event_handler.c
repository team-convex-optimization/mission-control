#include "event_handler.h"

void shutdown(void) {
    system("bash scripts/shutdown.sh");
}

void race_pipeline(void) {
    system("bash scripts/race.sh");
}

void reset_fundamentals(void) {
    system("bash scripts/fundamentals.sh");
}

void handle_rise_event(const int pin) {
    switch (pin)
    {
    case 140: 
        shutdown();
        break;
    case 7:
    case 8:
        race_pipeline();
        break;
    case 141:
    case 77:
        reset_fundamentals();
        break;
    default:
        break;
    }
}

void handle_fall_event(const int pin) {
    handle_rise_event(pin); /* Because we used SPSD switches, we see no distinction between fall/rise events at the moment */
}

void handle_event(const int pin, struct gpiod_line_event *event) {
    printf("event on pin %d\n", pin);
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

