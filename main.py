import os
import json
import subprocess
from dummy_data_gen import DummyDataGenerator

def files_in_dir(dir_path):
    return [f for f in os.listdir(dir_path) if os.path.isfile(os.path.join(dir_path, f))]

def get_relative_file_paths(directory):
    """
    Gets all files in a directory and returns their relative paths.

    Args:
        directory: The path to the directory.

    Returns:
        A list of relative file paths.
    """
    file_paths = []
    for root, _, files in os.walk(directory):
        for file in files:
            absolute_path = os.path.join(root, file)
            relative_path = os.path.relpath(absolute_path, directory)
            file_paths.append(relative_path)
    return file_paths
class EmbeddedTestAutomation:
    def __init__(self, config_json):
        """
        Initialize with the JSON configuration for components to test.
        :param config_json: JSON string or dict specifying which components to test (e.g., gpio, uart).
        """
        if isinstance(config_json, str):
            self.config = json.loads(config_json)
        else:
            self.config = config_json
        
        self.directories = [
            'src', 
            'mock', 
            'unit_tests', 
            'include', 
            'build', 
            'bin'
        ]

    def create_directories(self):
        """Create necessary directories for the project."""
        for directory in self.directories:
            if not os.path.exists(directory):
                os.makedirs(directory)
                print(f"Created directory: {directory}")
            else:
                print(f"Directory already exists: {directory}")

    def create_mock_files(self):
        """Generate mock files based on the components defined in the configuration."""
        if 'gpio' in self.config and self.config['gpio']:
            self.create_gpio_mock()
        if 'uart' in self.config and self.config['uart']:
            self.create_uart_mock()
        if 'shared_memory' in self.config and self.config['shared_memory']:
            self.create_shared_memory_mock()
        if 'registers' in self.config and self.config['registers']:
            self.create_registers_mock()

    def create_registers_mock(self):
        pass
    
    def create_uart_mock(self):
        pass

    def create_shared_memory_mock(self):
        pass

    def create_gpio_mock(self):
        """Create mock functions for GPIO."""
        gpio_mock_content = """
#include "gpio.h"
#include <stdio.h>

unsigned int gpio_pins[GPIO_PIN_COUNT] = {0};  // Mock GPIO pin values

void mock_write_gpio(unsigned int pin, unsigned int value) {
    if (pin < GPIO_PIN_COUNT) {
        gpio_pins[pin] = value;
        printf("GPIO Pin %u set to %u\\n", pin, value);
    }
}

unsigned int mock_read_gpio(unsigned int pin) {
    if (pin < GPIO_PIN_COUNT) {
        return gpio_pins[pin];
    }
    return 0;
}
"""
        with open("mock/gpio_mock.c", 'w') as file:
            file.write(gpio_mock_content)
        print("Created mock for GPIO.")

if __name__ == "__main__":
    uint_array = DummyDataGenerator.generate_unsigned_int_array(5)
    ushort_array = DummyDataGenerator.generate_unsigned_short_array(5)
    char_array = DummyDataGenerator.generate_char_array(10)
    byte_array = DummyDataGenerator.generate_byte_array(10)

    print("Unsigned Int Array:", uint_array)
    print("Unsigned Short Array:", ushort_array)
    print("Char Array:", char_array)
    print("Byte Array:", byte_array)

    print(get_relative_file_paths("unit_tests"))