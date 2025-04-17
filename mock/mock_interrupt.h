/**
 * @file mock_interrupt.h
 * @brief Provides mock functions to simulate interrupt handling.
 * 
 * This file defines the interface for mocking interrupt enable/disable
 * and handler registration for testing in an embedded environment.
 * 
 * @note These functions are mocked and do not interface with real hardware.
 */

 #ifndef MOCK_INTERRUPT_H
 #define MOCK_INTERRUPT_H
 
 #define MAX_INTERRUPTS 32 ///< Maximum number of supported mock interrupts
 
 typedef void (*interrupt_handler_t)(void);
 
 extern int interrupt_enabled[MAX_INTERRUPTS]; ///< Interrupt enable status
 extern interrupt_handler_t interrupt_handlers[MAX_INTERRUPTS]; ///< Registered interrupt handlers
 
 /**
  * @brief Mock function to enable an interrupt.
  * 
  * @param irq Interrupt number.
  */
 void mock_enable_interrupt(int irq);
 
 /**
  * @brief Mock function to disable an interrupt.
  * 
  * @param irq Interrupt number.
  */
 void mock_disable_interrupt(int irq);
 
 /**
  * @brief Mock function to register an interrupt handler.
  * 
  * @param irq Interrupt number.
  * @param handler Handler function to register.
  */
 void mock_register_interrupt_handler(int irq, interrupt_handler_t handler);
 
 /**
  * @brief Mock function to trigger a software interrupt.
  * 
  * @param irq Interrupt number to trigger.
  */
 void mock_trigger_interrupt(int irq);
 
 #endif // MOCK_INTERRUPT_H
 