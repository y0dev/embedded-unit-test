#include "unit_test.h"

#include "shared_memory.h"
#include "uart.h"
#include "registers.h"
#include "gpio.h"
#include "external_communication.h"

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