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

External Interrupt (EXTI)  
GPIO pins are connected to EXTI lines.  
It possible to enable interrupt for any GPIO pin  
Multiple pins share the same EXTI line  

pin0 of every port is connected to EXT10_IRQ  
pin1 of every port is connected to EXT11_IRQ  
pin2 of every port is connected to EXT12_IRQ  
pin3 of every port is connected to EXT13_IRQ

![image](https://github.com/user-attachments/assets/4c38f228-78ff-424c-a6a8-114738d315c1)


