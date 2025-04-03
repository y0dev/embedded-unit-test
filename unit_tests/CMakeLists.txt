# Enable testing for unit tests
enable_testing()

# Create a unit test executable for each test component
add_executable(test_shared_memory unit_tests/test_shared_memory.c)
add_executable(test_uart unit_tests/test_uart.c)
add_executable(test_registers unit_tests/test_registers.c)
add_executable(test_gpio unit_tests/test_gpio.c)
add_executable(test_external_communication unit_tests/test_external_communication.c)

# Link each test executable with the respective source and mock files
target_sources(test_shared_memory PRIVATE src/shared_memory/shared_memory.c mock/mock_shared_memory.c)
target_sources(test_uart PRIVATE src/uart/uart.c mock/mock_uart.c)
target_sources(test_registers PRIVATE src/registers/registers.c mock/mock_registers.c)
target_sources(test_gpio PRIVATE src/gpio/gpio.c mock/mock_gpio.c)
target_sources(test_external_communication PRIVATE src/external_communication/external_communication.c mock/mock_external_communication.c)

# Add the unit tests to CTest
add_test(NAME test_shared_memory COMMAND test_shared_memory)
add_test(NAME test_uart COMMAND test_uart)
add_test(NAME test_registers COMMAND test_registers)
add_test(NAME test_gpio COMMAND test_gpio)
add_test(NAME test_external_communication COMMAND test_external_communication)
