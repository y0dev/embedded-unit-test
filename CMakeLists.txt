# Set the minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(embedded_unit_test_app VERSION 1.0)

# Set the C standard
set(CMAKE_C_STANDARD 99)

# Add subdirectories for individual components
add_subdirectory(src)
add_subdirectory(mock)
add_subdirectory(unit_tests)

# Set the build output directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include directories for shared memory, uart, registers, gpio, and external communication
include_directories(src)
include_directories(mock)

# Define executable target for the unit test application
add_executable(embedded_unit_test_app
    src/main.c
    src/shared_memory/shared_memory.c
    src/uart/uart.c
    src/registers/registers.c
    src/gpio/gpio.c
    src/external_communication/external_communication.c
)

# Link mock functions to the target
target_sources(embedded_unit_test_app
    PRIVATE
    mock/mock_shared_memory.c
    mock/mock_uart.c
    mock/mock_registers.c
    mock/mock_gpio.c
    mock/mock_external_communication.c
)

# Optional: Enable testing with CTest
enable_testing()
