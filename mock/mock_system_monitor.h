#ifndef MOCK_SYSTEM_MONITOR_H
#define MOCK_SYSTEM_MONITOR_H

#include <stdio.h>

/**
 * @brief Mock function to simulate getting CPU usage percentage.
 * 
 * @return The simulated CPU usage as a percentage (0-100).
 */
int mock_get_cpu_usage(void);

/**
 * @brief Mock function to simulate getting memory usage in megabytes.
 * 
 * @return The simulated memory usage in MB.
 */
int mock_get_memory_usage(void);

/**
 * @brief Mock function to simulate getting available disk space in gigabytes.
 * 
 * @return The simulated available disk space in GB.
 */
int mock_get_disk_space(void);

/**
 * @brief Mock function to simulate checking if the system is idle.
 * 
 * @return 1 if the system is idle, 0 otherwise.
 */
int mock_is_system_idle(void);

/**
 * @brief Mock function to simulate getting system temperature.
 * 
 * @return The simulated system temperature in Celsius.
 */
float mock_get_system_temperature(void);

/**
 * @brief Mock function to simulate getting the system's voltage.
 * 
 * @return The simulated system voltage in volts (e.g., 3.3V, 5.0V, etc.).
 */
float mock_get_system_voltage(void);

/**
 * @brief Mock function to simulate getting an auxiliary integer value.
 * 
 * @return The simulated auxiliary integer value (e.g., a status code or metric).
 */
int mock_get_auxiliary_value(void);

#endif // MOCK_SYSTEM_MONITOR_H
