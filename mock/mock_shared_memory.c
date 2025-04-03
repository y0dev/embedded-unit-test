/**
 * @file mock_shared_memory.c
 * @brief Provides mock functions to simulate shared memory operations.
 * 
 * This file contains mock functions to simulate reading and writing to shared memory.
 * 
 * @note The shared memory functions are mocked for testing purposes only.
 */

 #include "mock/mock_shared_memory.h"
 #include <string.h>
 
 unsigned char shared_memory[SHARED_MEMORY_SIZE] = {0}; ///< Array to represent shared memory
 
 int mock_write_shared_memory(unsigned int offset, const unsigned char *data, unsigned int len) {
     if (offset + len <= SHARED_MEMORY_SIZE) {
         memcpy(&shared_memory[offset], data, len);
         printf("Writing %u bytes to shared memory at offset %u\n", len, offset);
         return 0; // Success
     }
     printf("Error: Out of bounds write to shared memory\n");
     return -1; // Error
 }
 
 int mock_read_shared_memory(unsigned int offset, unsigned char *buffer, unsigned int len) {
     if (offset + len <= SHARED_MEMORY_SIZE) {
         memcpy(buffer, &shared_memory[offset], len);
         printf("Reading %u bytes from shared memory at offset %u\n", len, offset);
         return 0; // Success
     }
     printf("Error: Out of bounds read from shared memory\n");
     return -1; // Error
 }
 