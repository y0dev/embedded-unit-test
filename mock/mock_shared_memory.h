/**
 * @file mock_shared_memory.h
 * @brief Provides mock functions to simulate shared memory operations.
 * 
 * This file contains mock functions to simulate reading and writing to shared memory.
 * 
 * @note The shared memory functions are mocked for testing purposes only.
 */

 #ifndef MOCK_SHARED_MEMORY_H
 #define MOCK_SHARED_MEMORY_H
 
 #define SHARED_MEMORY_SIZE 1024 ///< The size of the mock shared memory
 
 extern unsigned char shared_memory[SHARED_MEMORY_SIZE]; ///< Array to represent shared memory
 
 /**
  * @brief Mock function to write to shared memory.
  * 
  * @param offset The memory offset to write to.
  * @param data The data to write.
  * @param len The length of the data.
  * @return 0 if successful, -1 if an error occurs.
  * @note This function simulates writing data to shared memory.
  */
 int mock_write_shared_memory(unsigned int offset, const unsigned char *data, unsigned int len);
 
 /**
  * @brief Mock function to read from shared memory.
  * 
  * @param offset The memory offset to read from.
  * @param buffer The buffer to store the read data.
  * @param len The length of data to read.
  * @return 0 if successful, -1 if an error occurs.
  * @note This function simulates reading data from shared memory.
  */
 int mock_read_shared_memory(unsigned int offset, unsigned char *buffer, unsigned int len);
 
 #endif // MOCK_SHARED_MEMORY_H
 