/**
 * @file mock_gpio.h
 * @brief Provides mock functions to simulate GPIO pin operations.
 * 
 * This file contains mock functions to simulate reading and writing to GPIO pins.
 * 
 * @note The GPIO functions are mocked for testing purposes only.
 */

 #ifndef MOCK_GPIO_H
 #define MOCK_GPIO_H
 
 #define GPIO_PIN_COUNT 8 ///< The number of mock GPIO pins
 
 extern unsigned int gpio_pins[GPIO_PIN_COUNT]; ///< Array to represent GPIO pins
 
 /**
  * @brief Mock function to write to a GPIO pin.
  * 
  * @param pin The GPIO pin number.
  * @param value The value to write (0 or 1).
  * @note The function simulates writing a value to a GPIO pin.
  */
 void mock_write_gpio(unsigned int pin, unsigned int value);
 
 /**
  * @brief Mock function to read from a GPIO pin.
  * 
  * @param pin The GPIO pin number.
  * @return The value of the GPIO pin (0 or 1).
  * @note The function simulates reading a value from a GPIO pin.
  */
 unsigned int mock_read_gpio(unsigned int pin);
 
 #endif // MOCK_GPIO_H
 