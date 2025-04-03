#include <assert.h>
#include "mock/mock_external_communication.h"

/**
 * @brief Unit test for external network communication.
 * 
 * This test verifies that mock functions for opening a connection, sending
 * data, receiving data, and closing the connection work as expected.
 */
void test_external_communication(void) {
    char buffer[256];
    
    // Simulate opening the connection
    assert(mock_open_connection("127.0.0.1", 8080) == 0);
    
    // Simulate sending data
    const char *data_to_send = "Test message";
    assert(mock_send_data(data_to_send, strlen(data_to_send)) == strlen(data_to_send));
    
    // Simulate receiving data
    assert(mock_receive_data(buffer, sizeof(buffer)) > 0);
    
    // Simulate closing the connection
    assert(mock_close_connection() == 0);
}
