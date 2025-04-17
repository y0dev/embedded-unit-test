#include <assert.h>
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
    assert(mock_write_shared_memory(100, data_to_write, sizeof(data_to_write)) == 0);
    
    // Read from shared memory
    assert(mock_read_shared_memory(100, buffer, sizeof(buffer)) == 0);
    assert(buffer[0] == 1);
    assert(buffer[1] == 2);
    assert(buffer[2] == 3);
    assert(buffer[3] == 4);
    
    // Invalid memory access test
    assert(mock_read_shared_memory(1024, buffer, sizeof(buffer)) == -1);  // Invalid offset
}
