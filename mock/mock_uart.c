/**
 * @file mock_uart.c
 * @brief Provides mock functions to simulate UART operations.
 * 
 * This file contains mock functions to simulate UART communication.
 * 
 * @note The UART functions are mocked for testing purposes only.
 */

 #include "mock_uart.h"
 #include <string.h>
 #include <stdio.h>
 
 int mock_uart_transmit(const char *data, unsigned int len) {
     printf("Transmitting data over UART: %.*s\n", len, data);
     return len; // Return number of bytes transmitted
 }
 
 int mock_uart_receive(char *buffer, unsigned int len) {
     const char *mock_data = "Mock UART Data"; 
     strncpy(buffer, mock_data, len);
     printf("Receiving data over UART: %s\n", buffer);
     return strlen(mock_data); // Return number of bytes received
 }
 