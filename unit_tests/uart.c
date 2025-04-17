#include <assert.h>
#include "mock_uart.h"
 #include <string.h>

/**
 * @brief Unit test for UART operations.
 * 
 * This test verifies that mock functions for transmitting and receiving data 
 * over UART work as expected.
 */
void test_uart_operations(void) {
    char buffer[64];
    
    // Transmit data over UART
    assert(mock_uart_transmit("Hello, UART!", 12) == 12);
    
    // Receive data over UART
    int bytes_received = mock_uart_receive(buffer, sizeof(buffer));
    assert(bytes_received == 14);
    assert(strcmp(buffer, "Mock UART Data") == 0);
}
