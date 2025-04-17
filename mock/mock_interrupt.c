/**
 * @file mock_interrupt.c
 * @brief Implements mock interrupt handling functions.
 * 
 * Simulates enabling, disabling, registering, and triggering of interrupts
 * in a test environment.
 * 
 * @note This is for unit testing only and does not interface with actual hardware.
 */

 #include "mock_interrupt.h"
 #include <stdio.h>
 
 int interrupt_enabled[MAX_INTERRUPTS] = {0};
 interrupt_handler_t interrupt_handlers[MAX_INTERRUPTS] = {0};
 
 void mock_enable_interrupt(int irq) {
     if (irq >= 0 && irq < MAX_INTERRUPTS) {
         interrupt_enabled[irq] = 1;
         printf("Interrupt %d enabled\n", irq);
     }
 }
 
 void mock_disable_interrupt(int irq) {
     if (irq >= 0 && irq < MAX_INTERRUPTS) {
         interrupt_enabled[irq] = 0;
         printf("Interrupt %d disabled\n", irq);
     }
 }
 
 void mock_register_interrupt_handler(int irq, interrupt_handler_t handler) {
     if (irq >= 0 && irq < MAX_INTERRUPTS) {
         interrupt_handlers[irq] = handler;
         printf("Handler registered for interrupt %d\n", irq);
     }
 }
 
 void mock_trigger_interrupt(int irq) {
     if (irq >= 0 && irq < MAX_INTERRUPTS && interrupt_enabled[irq]) {
         printf("Interrupt %d triggered\n", irq);
         if (interrupt_handlers[irq]) {
             interrupt_handlers[irq](); // call the handler
         } else {
             printf("No handler registered for interrupt %d\n", irq);
         }
     }
 }
 