/**
 * @file mock_mailbox.h
 * @brief Provides mock functions to simulate a mailbox for inter-process or inter-core communication.
 * 
 * This file defines a mock mailbox interface for testing message passing between components
 * in an embedded environment.
 * 
 * @note These functions are mocked and intended only for simulation/testing purposes.
 */

 #ifndef MOCK_MAILBOX_H
 #define MOCK_MAILBOX_H
 
 #define MAILBOX_MAX_MESSAGES 16    ///< Maximum number of messages in the mailbox
 #define MAILBOX_MSG_SIZE     64    ///< Maximum size of each message (in bytes)
 
 #include <stddef.h>
 #include <stdint.h>
 
 /**
  * @brief Mock function to initialize the mailbox system.
  */
 void mock_mailbox_init(void);
 
 /**
  * @brief Mock function to send a message to the mailbox.
  * 
  * @param msg Pointer to the message data.
  * @param len Length of the message to send.
  * @return 0 on success, -1 if mailbox is full or error occurs.
  */
 int mock_mailbox_send(const void *data, size_t len);
 
 /**
  * @brief Mock function to receive a message from the mailbox.
  * 
  * @param buffer Pointer to buffer where the message will be copied.
  * @param max_len Maximum buffer size to receive.
  * @return Number of bytes received, or -1 if mailbox is empty or error occurs.
  */
 int mock_mailbox_receive(void *buffer, size_t max_len);
 
 #endif // MOCK_MAILBOX_H
 