#include "shared_memory.h"
#include "uart.h"
#include "registers.h"
#include "gpio.h"
#include "external_communication.h"

int main(void) {
    // Here you can call test functions or use your components in a simple test environment.
    test_shared_memory();
    test_uart();
    test_registers();
    test_gpio();
    test_external_communication();

    return 0;
}
