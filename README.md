# Mock Functions for GPIO, Shared Memory, Register Read/Write, and UART

This project includes mock implementations for testing hardware-related operations, such as GPIO pin operations, shared memory access, register read/write operations, and UART communication. These mock functions are designed to simulate hardware interactions and allow for unit testing without the need for actual hardware.

## Project Structure

├── src/ # Source files containing main application logic
├── mock/ # Mock implementations of hardware functions (GPIO, shared memory, etc.)
├── unit_tests/ # Unit test files for testing mock functions
├── include/ # Header files for declarations
├── Makefile # Build automation tool

## Prerequisites

Ensure you have the following installed:

- **GCC** (GNU Compiler Collection)
- **Make** (for build automation)

## Setup

1. Clone the repository:

   ```bash
   git clone https://github.com/y0dev/embedded-unit-test.git
   cd embedded-unit-test
   ```

2. Build the project:

   Run the `make` command to compile and link the code:

   ```bash
   make
   ```

   This will compile all source files, generate object files, and produce an executable called `test_app`.

## Running Tests

After building the project, you can run the tests by executing the following command:

```bash
./test_app
```

This will execute the unit tests for GPIO, shared memory, register read/write, and UART functionalities.

## Writing Unit Tests

The unit tests for each module (GPIO, shared memory, etc.) are located in the unit_tests directory. Each test verifies the correctness of the corresponding mock function.

For example:

- GPIO tests are in unit_tests/test_gpio.c
- Shared memory tests are in unit_tests/test_shared_memory.c
- Register read/write tests are in unit_tests/test_register.c
- UART tests are in unit_tests/test_uart.c

You can modify or add new tests as needed to cover additional cases.

## Cleaning Up

To clean up the object files and the executable, run:

```bash
make clean
```

## License

This project is licensed under the MIT License - see the LICENSE file for details.

### Key Sections in README:

- **Project Structure**: Describes the folder layout and purpose of each directory/file.
- **Prerequisites**: Lists necessary software (GCC, Make).
- **Setup**: Provides instructions to clone the repo and build the project using `make`.
- **Running Tests**: Details how to execute the tests.
- **Writing Unit Tests**: Explains where to find and how to modify unit tests.
- **Cleaning Up**: Provides a command to clean up build artifacts.
- **License**: Mentions the project license (MIT, for example).
