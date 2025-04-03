#include <assert.h>
#include "mock/mock_gpio.h"

/**
 * @brief Unit test for GPIO operations.
 * 
 * This test verifies that mock functions for reading and writing to GPIO pins 
 * work as expected.
 */
void test_gpio_operations(void) {
    // Write to GPIO pins
    mock_write_gpio(2, 1);
    mock_write_gpio(4, 0);
    
    // Read from GPIO pins
    assert(mock_read_gpio(2) == 1);
    assert(mock_read_gpio(4) == 0);
    
    // Invalid pin test
    assert(mock_read_gpio(10) == 0);  // Invalid pin
}
