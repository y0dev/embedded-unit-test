#include "mock_system_monitor.h"
#include <stdlib.h>

int mock_get_cpu_usage(void) {
    // Simulating a random CPU usage between 0 and 100
    return rand() % 101; // Random value between 0 and 100
}

int mock_get_memory_usage(void) {
    // Simulating a random memory usage value between 0 and 16384 MB (16 GB)
    return rand() % 16385; // Random value between 0 and 16384
}

int mock_get_disk_space(void) {
    // Simulating available disk space between 0 and 500 GB
    return rand() % 501; // Random value between 0 and 500
}

int mock_is_system_idle(void) {
    // Simulating that the system is idle 50% of the time
    return rand() % 2; // 50% chance of being idle (1 for idle, 0 for not idle)
}

float mock_get_system_temperature(void) {
    // Simulating a system temperature between 30.0 and 90.0 degrees Celsius
    return 30.0 + (rand() % 601) / 10.0; // Random value between 30.0 and 90.0
}

float mock_get_system_voltage(void) {
    // Simulating a system voltage between 3.0 and 5.0 volts
    return 3.0 + (rand() % 201) / 100.0; // Random value between 3.0V and 5.0V
}

int mock_get_auxiliary_value(void) {
    // Simulating an auxiliary integer value between 0 and 1000
    return rand() % 1001; // Random value between 0 and 1000
}
