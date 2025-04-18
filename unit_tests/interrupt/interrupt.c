#include "mock_interrupt.h"
#include "unit_test.h"  // Assert MACROS
#include <stdio.h>

static int handler_call_count = 0;
static int last_handled_irq = -1;


// Sample interrupt handler
void test_interrupt_handler(void) {
    handler_call_count++;
}

// Another handler to test dynamic switching
void test_handler_with_irq_capture(void) {
    handler_call_count++;
    last_handled_irq = 5;
}

void test_interrupt_enable_disable() {
    int irq = 3;

    mock_disable_interrupt(irq);
    AssertIntEQ(interrupt_enabled[irq], 0);

    mock_enable_interrupt(irq);
    AssertIntEQ(interrupt_enabled[irq], 1);
}

void test_register_and_trigger_interrupt() {
    int irq = 1;
    handler_call_count = 0;

    mock_disable_interrupt(irq);  // Should not be triggered when disabled
    mock_register_interrupt_handler(irq, test_interrupt_handler);
    mock_trigger_interrupt(irq);
    AssertIntEQ(handler_call_count, 0);

    mock_enable_interrupt(irq);   // Enable and try again
    mock_trigger_interrupt(irq);
    AssertIntEQ(handler_call_count, 1);

    // Trigger again to confirm it accumulates
    mock_trigger_interrupt(irq);
    AssertIntEQ(handler_call_count, 2);
}

void test_interrupt_handler_switching() {
    int irq = 5;
    handler_call_count = 0;
    last_handled_irq = -1;

    mock_enable_interrupt(irq);
    mock_register_interrupt_handler(irq, test_handler_with_irq_capture);
    mock_trigger_interrupt(irq);

    AssertIntEQ(handler_call_count, 1);
    AssertIntEQ(last_handled_irq, irq);
}

void test_invalid_interrupts_are_ignored() {
    int invalid_irq = -1;
    mock_trigger_interrupt(invalid_irq);  // Should not crash

    invalid_irq = MAX_INTERRUPTS + 1;
    mock_trigger_interrupt(invalid_irq);  // Out-of-range, no-op
}
