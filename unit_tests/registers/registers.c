#include "unit_test.h"
#include "mock_registers.h"

/**
 * @brief Unit test for register operations.
 * 
 * This test verifies that mock functions for reading and writing to hardware registers 
 * work as expected.
 */
void test_register_operations(void) {
    // Write to registers
    mock_write_register(2, 1234);
    mock_write_register(4, 5678);
    
    // Read from registers
    AssertIntEQ(mock_read_register(2), 1234);
    AssertIntEQ(mock_read_register(4), 5678);
    
    // Invalid register access test
    AssertIntEQ(mock_read_register(10), 0);  // Invalid register index
}
