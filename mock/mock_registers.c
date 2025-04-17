/**
 * @file mock_register.c
 * @brief Provides mock functions to simulate register read/write operations.
 * 
 * This file contains mock functions to simulate reading and writing to hardware registers.
 * 
 * @note The register functions are mocked for testing purposes only.
 */

 #include "mock_registers.h"
 #include <stdio.h>

 unsigned int registers[REGISTER_COUNT] = {0}; ///< Array to represent hardware registers
 
 void mock_write_register(unsigned int reg, unsigned int value) {
     if (reg < REGISTER_COUNT) {
         registers[reg] = value;
         printf("Writing value %u to register %u\n", value, reg);
     } else {
         printf("Invalid register index %u\n", reg);
     }
 }
 
 unsigned int mock_read_register(unsigned int reg) {
     if (reg < REGISTER_COUNT) {
         printf("Reading value from register %u: %u\n", reg, registers[reg]);
         return registers[reg];
     }
     printf("Invalid register index %u\n", reg);
     return 0; // Default value for invalid register
 }
 