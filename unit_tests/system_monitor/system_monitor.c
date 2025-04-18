#include "unit_test.h"
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
    AssertIntInRange(cpu_usage, 0, 100);
    
    // Simulate getting memory usage
    int memory_usage = mock_get_memory_usage();
    AssertIntInRange(memory_usage, 0,16384); // Assuming max memory is 16 GB
    
    // Simulate getting disk space
    int disk_space = mock_get_disk_space();
    AssertIntInRange(disk_space, 0, 500); // Assuming max disk space is 500 GB
    
    // Simulate checking if the system is idle
    int is_idle = mock_is_system_idle();
    AssertIsBinary(is_idle); // System should either be idle or not
    
    // Simulate getting system temperature
    float system_temperature = mock_get_system_temperature();
    AssertDoubleInRange(system_temperature, 30.0, 90.0); // Assuming temperature range
    
    // Simulate getting system voltage
    float system_voltage = mock_get_system_voltage();
    AssertDoubleInRange(system_voltage, 3.0 , 5.0); // Assuming voltage range
    
    // Simulate getting auxiliary value
    int auxiliary_value = mock_get_auxiliary_value();
    AssertIntInRange(auxiliary_value, 0, 1000); // Assuming range for auxiliary value
}
