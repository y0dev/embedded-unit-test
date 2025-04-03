/**
 * @file mock_register.h
 * @brief Provides mock functions to simulate register read/write operations.
 * 
 * This file contains mock functions to simulate reading and writing to hardware registers.
 * 
 * @note The register functions are mocked for testing purposes only.
 */

 #ifndef MOCK_REGISTER_H
 #define MOCK_REGISTER_H
 
 #define REGISTER_COUNT 8 ///< The number of mock hardware registers
 
 extern unsigned int registers[REGISTER_COUNT]; ///< Array to represent hardware registers
 
 /**
  * @brief Mock function to write to a hardware register.
  * 
  * @param reg The register index to write to.
  * @param value The value to write to the register.
  * @note The function simulates writing to a hardware register.
  */
 void mock_write_register(unsigned int reg, unsigned int value);
 
 /**
  * @brief Mock function to read from a hardware register.
  * 
  * @param reg The register index to read from.
  * @return The value of the hardware register.
  * @note The function simulates reading from a hardware register.
  */
 unsigned int mock_read_register(unsigned int reg);
 
 #endif // MOCK_REGISTER_H
 