#ifndef MOCK_EXTERNAL_COMMUNICATION_H
#define MOCK_EXTERNAL_COMMUNICATION_H

/**
 * @brief Mock function to simulate opening a network connection.
 * 
 * @param ip The IP address of the server.
 * @param port The port number to connect to.
 * @return 0 if connection is successful, -1 otherwise.
 */
int mock_open_connection(const char *ip, unsigned int port);

/**
 * @brief Mock function to simulate closing a network connection.
 * 
 * @return 0 if connection is closed successfully, -1 otherwise.
 */
int mock_close_connection(void);

/**
 * @brief Mock function to simulate sending data over a network connection.
 * 
 * @param data The data to send.
 * @param len The length of data to send.
 * @return The number of bytes sent.
 */
int mock_send_data(const char *data, unsigned int len);

/**
 * @brief Mock function to simulate receiving data from a network connection.
 * 
 * @param buffer The buffer to store received data.
 * @param len The length of data to receive.
 * @return The number of bytes received.
 */
int mock_receive_data(char *buffer, unsigned int len);

#endif // MOCK_EXTERNAL_COMMUNICATION_H
