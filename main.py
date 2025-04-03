import os
import json
import subprocess

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