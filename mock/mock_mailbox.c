/**
 * @file mock_mailbox.c
 * @brief Implements mock mailbox message passing functions.
 * 
 * Simulates mailbox message queuing and retrieval for testing environments
 * where inter-process or inter-core communication is required.
 * 
 * @note This is for unit testing and does not implement actual hardware mailbox interfaces.
 */

 #include "mock_mailbox.h"
 #include <string.h>
 #include <stdio.h>
 
 static uint8_t mailbox[MAILBOX_MAX_MESSAGES][MAILBOX_MSG_SIZE];
 static size_t message_lengths[MAILBOX_MAX_MESSAGES];
 static int head = 0;
 static int tail = 0;
 static int count = 0;
 
 void mock_mailbox_init(void) {
     head = tail = count = 0;
     memset(mailbox, 0, sizeof(mailbox));
     memset(message_lengths, 0, sizeof(message_lengths));
     printf("Mailbox initialized.\n");
 }
 
 int mock_mailbox_send(const uint8_t *msg, size_t len) {
     if (count >= MAILBOX_MAX_MESSAGES || len > MAILBOX_MSG_SIZE) {
         printf("Mailbox full or message too large.\n");
         return -1;
     }
 
     memcpy(mailbox[tail], msg, len);
     message_lengths[tail] = len;
     tail = (tail + 1) % MAILBOX_MAX_MESSAGES;
     count++;
 
     printf("Message sent. Length: %zu\n", len);
     return 0;
 }
 
 int mock_mailbox_receive(uint8_t *buffer, size_t max_len) {
     if (count == 0) {
         printf("Mailbox empty.\n");
         return -1;
     }
 
     size_t len = message_lengths[head];
     if (len > max_len) len = max_len;
 
     memcpy(buffer, mailbox[head], len);
     head = (head + 1) % MAILBOX_MAX_MESSAGES;
     count--;
 
     printf("Message received. Length: %zu\n", len);
     return (int)len;
 }
 
 void mock_mailbox_clear(void) {
     head = tail = count = 0;
     memset(mailbox, 0, sizeof(mailbox));
     memset(message_lengths, 0, sizeof(message_lengths));
     printf("Mailbox cleared.\n");
 }
 