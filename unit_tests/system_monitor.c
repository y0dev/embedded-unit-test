#include <assert.h>
#include "mock_system_monitor.h"

/**
 * @brief Unit test for the mock system monitor.
 * 
 * This test verifies that the mock functions for getting system stats
 * such as CPU usage, memory usage, disk space, system idle state, 
 * system temperature, system voltage, and auxiliary value work as expected.
 */
void test_system_monitor(void) {
    // Simulate getting CPU usage
    int cpu_usage = mock_get_cpu_usage();
    assert(cpu_usage >= 0 && cpu_usage <= 100);
    
    // Simulate getting memory usage
    int memory_usage = mock_get_memory_usage();
    assert(memory_usage >= 0 && memory_usage <= 16384); // Assuming max memory is 16 GB
    
    // Simulate getting disk space
    int disk_space = mock_get_disk_space();
    assert(disk_space >= 0 && disk_space <= 500); // Assuming max disk space is 500 GB
    
    // Simulate checking if the system is idle
    int is_idle = mock_is_system_idle();
    assert(is_idle == 0 || is_idle == 1); // System should either be idle or not
    
    // Simulate getting system temperature
    float system_temperature = mock_get_system_temperature();
    assert(system_temperature >= 30.0 && system_temperature <= 90.0); // Assuming temperature range
    
    // Simulate getting system voltage
    float system_voltage = mock_get_system_voltage();
    assert(system_voltage >= 3.0 && system_voltage <= 5.0); // Assuming voltage range
    
    // Simulate getting auxiliary value
    int auxiliary_value = mock_get_auxiliary_value();
    assert(auxiliary_value >= 0 && auxiliary_value <= 1000); // Assuming range for auxiliary value
}
