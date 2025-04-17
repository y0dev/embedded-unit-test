#include "unit_test.h"

#include "shared_memory.h"
#include "uart.h"
#include "registers.h"
#include "gpio.h"
#include "external_communication.h"
#include "mailbox.h"
#include "interrupt.h"

int totalTested = 0;
int totalPassed = 0;
int totalFailed = 0;
int totalSkipped = 0;


void run_tests(void)
{
    // Here you can call test functions or use your components in a simple test environment.
    test_shared_memory_operations();
    test_uart_operations();
    test_register_operations();
    test_gpio_operations();
    test_external_communication();


    printf("Running interrupt tests...\n");
    // test_interrupt_handler();
    // test_handler_with_irq_capture();

    test_interrupt_enable_disable();
    test_register_and_trigger_interrupt();
    test_interrupt_handler_switching();
    test_invalid_interrupts_are_ignored();
    printf("Interrupt tests complete.\n");

    test_mock_mailbox_send_receive_struct();
}

void print_test_results(void)
{
    printf("\n==============================\n");
    printf("      Unit Test Summary       \n");
    printf("==============================\n");
    printf("Total Tests Run   : %d\n", totalTested);
    printf("Tests Passed      : %d\n", totalPassed);
    printf("Tests Failed      : %d\n", totalFailed);
    printf("Tests Skipped     : %d\n", totalSkipped);
    printf("==============================\n");

    if (totalFailed == 0) {
        printf("✅ ALL TESTS PASSED ✅\n");
    } else {
        printf("❌ SOME TESTS FAILED ❌\n");
    }
    printf("==============================\n\n");
}