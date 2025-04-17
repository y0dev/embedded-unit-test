/**
 * @file mock_gpio.c
 * @brief Provides mock functions to simulate GPIO pin operations.
 * 
 * This file contains mock functions to simulate reading and writing to GPIO pins.
 * 
 * @note The GPIO functions are mocked for testing purposes only.
 */

 #include "mock_gpio.h"
 #include <stdio.h>

 unsigned int gpio_pins[GPIO_PIN_COUNT] = {0}; ///< Array to represent GPIO pins
 
 void mock_write_gpio(unsigned int pin, unsigned int value) {
     if (pin < GPIO_PIN_COUNT) {
         gpio_pins[pin] = value;
         printf("Writing value %u to GPIO pin %u\n", value, pin);
     } else {
         printf("Invalid GPIO pin %u\n", pin);
     }
 }
 
 unsigned int mock_read_gpio(unsigned int pin) {
     if (pin < GPIO_PIN_COUNT) {
         printf("Reading value from GPIO pin %u: %u\n", pin, gpio_pins[pin]);
         return gpio_pins[pin];
     }
     printf("Invalid GPIO pin %u\n", pin);
     return 0; // Default value if the pin is invalid
 }
 