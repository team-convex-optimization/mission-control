#include <gpiod.h>
#include <stdio.h>


#define PIN_COUNT 5
extern const int PINS[PIN_COUNT];

/**
 * @brief Handle an event on pin @p pin
 * 
 * @param pin the pin number
 * @param event the event to handle
 */
void handle_event(const int pin, struct gpiod_line_event *event);