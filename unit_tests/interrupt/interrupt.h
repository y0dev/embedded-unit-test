#ifndef INTERRUPT_H
#define INTERRUPT_H

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Test enabling and disabling interrupts.
 */
void test_interrupt_enable_disable(void);

/**
 * @brief Test registering and triggering an interrupt handler.
 */
void test_register_and_trigger_interrupt(void);

/**
 * @brief Test switching interrupt handlers.
 */
void test_interrupt_handler_switching(void);

/**
 * @brief Test handling of invalid interrupt numbers.
 */
void test_invalid_interrupts_are_ignored(void);

#ifdef __cplusplus
}
#endif

#endif // INTERRUPT_H
