#include "unit_test.h"
#include "mock_shared_memory.h"

/**
 * @brief Unit test for shared memory operations.
 * 
 * This test verifies that mock functions for reading and writing to shared memory 
 * work as expected.
 */
void test_shared_memory_operations(void) {
    unsigned char data_to_write[] = {1, 2, 3, 4};
    unsigned char buffer[4];
    
    // Write to shared memory
    AssertIntEQ(mock_write_shared_memory(100, data_to_write, sizeof(data_to_write)), 0);
    
    // Read from shared memory
    AssertIntEQ(mock_read_shared_memory(100, buffer, sizeof(buffer)), 0);
    AssertIntEQ(buffer[0], 1);
    AssertIntEQ(buffer[1], 2);
    AssertIntEQ(buffer[2], 3);
    AssertIntEQ(buffer[3], 4);
    
    // Invalid memory access test
    AssertIntEQ(mock_read_shared_memory(1024, buffer, sizeof(buffer)), -1);  // Invalid offset
}
