Interrupt :  
when module needs service, it notifies the CPU by sending an interrupt signal. When the CPU receives the signal, the CPU interrupts whatever it is doing and services the module  

Polling :
the CPU continuously monitors the status of a given module, when a particular status condition is met, the CPU then services the module

ISR - interrupt serivice routine  

The function that gets executed when an interrupt occurs is called the interrupt service routine (ISR) or interrupt handler  

Nest Vector Interrupt Controller (NVIC):
a dedicated hardware inside the cortex-microcontroller
it is responsible for handling interrupts

CSS - clock security system  

interrupts from the processor core are known as 'exceptions'
interrupts from outside the processor core are known as 'hardware exceptions' or 'interrupt request'  

interrupt handlers  
exception handlers  

