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

every ports : PA,PB,PC,PD,etc

![image](https://github.com/user-attachments/assets/4c38f228-78ff-424c-a6a8-114738d315c1)

interrupt states:
disabled - this is the default state
enabled - interupt is enabled
pending - waiting to be serviced
active - being serviced

![image](https://github.com/user-attachments/assets/85f918eb-352e-4dad-ae0d-2e1dbfb9e079)

priorities allow us to set which interrupt should execute first.  
they also allow us to set which interrupt can interrupt which.  

<vector table for stm32f411>

some interrupt priorities are defined by ARM, these cannot be changed.  
Eg:  
1st priority - HardFault  
2nd priority - NMI  
3rd priority - RESET

IPR - interrupt priority register  (32-bits)
each IRQ uses 8-bits inside a single IPR reg  
therefore one IPR reg allows us to configure the priorities of 4 different interrupt requests  
Eg : IPR0 holds priorities of IRQ0.IRQ1,IRQ2 and IRQ3  
there are 60 IPR regs : IPR0 - 1PR59  
there are 60*4 = 240 IRQs  

stm32 microcontrollers use only the upper 4 bits of 8 bits to configure the priority of each IRQ  
this implies that in STM32 MCUs there are 2^4 = 16 priority levels  
























