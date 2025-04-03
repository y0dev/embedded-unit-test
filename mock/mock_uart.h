/**
 * @file mock_uart.h
 * @brief Provides mock functions to simulate UART operations.
 * 
 * This file contains mock functions to simulate UART communication.
 * 
 * @note The UART functions are mocked for testing purposes only.
 */

 #ifndef MOCK_UART_H
 #define MOCK_UART_H
 
 /**
  * @brief Mock function to simulate transmitting data over UART.
  * 
  * @param data The data to send.
  * @param len The length of the data.
  * @return The number of bytes transmitted.
  * @note This function simulates sending data over UART.
  */
 int mock_uart_transmit(const char *data, unsigned int len);
 
 /**
  * @brief Mock function to simulate receiving data over UART.
  * 
  * @param buffer The buffer to store received data.
  * @param len The length of data to receive.
  * @return The number of bytes received.
  * @note This function simulates receiving data over UART.
  */
 int mock_uart_receive(char *buffer, unsigned int len);
 
 #endif // MOCK_UART_H
 