/**
 * @file mock_external_communication.c
 * @brief Implements mock functions for external network communication.
 * 
 * This file implements the functions to simulate sending and receiving data 
 * over a network connection (TCP/UDP).
 * 
 * @note The functions are mocked for testing purposes only and do not interact 
 *       with real network hardware.
 */

 #include "mock/mock_external_communication.h"
 #include <stdio.h>
 #include <string.h>
 
 /**
  * @brief Mock function to simulate opening a network connection.
  * 
  * @param ip The IP address of the server.
  * @param port The port number to connect to.
  * @return 0 if connection is successful, -1 otherwise.
  * @note This function just simulates a successful connection.
  */
 int mock_open_connection(const char *ip, unsigned int port) {
     printf("Opening connection to IP: %s, Port: %u\n", ip, port);
     // Simulate a successful connection
     return 0;
 }
 
 /**
  * @brief Mock function to simulate closing a network connection.
  * 
  * @return 0 if connection is closed successfully, -1 otherwise.
  * @note This function just simulates closing a connection.
  */
 int mock_close_connection(void) {
     printf("Closing connection.\n");
     // Simulate a successful close
     return 0;
 }
 
 /**
  * @brief Mock function to simulate sending data over a network connection.
  * 
  * @param data The data to send.
  * @param len The length of data to send.
  * @return The number of bytes sent.
  * @note This function just prints the data and simulates sending it.
  */
 int mock_send_data(const char *data, unsigned int len) {
     printf("Sending data: %.*s\n", len, data);
     // Simulate the number of bytes sent (for simplicity, return length of data)
     return len;
 }
 
 /**
  * @brief Mock function to simulate receiving data from a network connection.
  * 
  * @param buffer The buffer to store received data.
  * @param len The length of data to receive.
  * @return The number of bytes received.
  * @note This function just fills the buffer with mock data.
  */
 int mock_receive_data(char *buffer, unsigned int len) {
     const char *mock_data = "Mock received data from server.";
     unsigned int mock_data_len = strlen(mock_data);
     
     // Simulate receiving data and filling the buffer
     unsigned int data_len_to_copy = (len < mock_data_len) ? len : mock_data_len;
     strncpy(buffer, mock_data, data_len_to_copy);
     printf("Received data: %.*s\n", data_len_to_copy, buffer);
     
     return data_len_to_copy;
 }
 