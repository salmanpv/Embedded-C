#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
// #include "uart.h"
// #include "adc.h"

// =======================
// SYSTICK DEFINITIONS
// =======================

#define SYSTICK_LOAD_VAL    16000
#define CTRL_ENABLE         (1U << 0)
#define CTRL_CLKSRC         (1U << 2)
#define CTRL_COUNTFLAG      (1U << 16)

// Function Prototype
void systickDelayMs(int delay);

// =======================
// SYSTICK FUNCTION
// =======================

void systickDelayMs(int delay)
{
    /* Reload with number of clocks per millisecond */
    SysTick->LOAD = SYSTICK_LOAD_VAL;

    /* Clear systick current value register */
    SysTick->VAL = 0;

    /* Enable systick and select internal clk src */
    SysTick->CTRL = CTRL_ENABLE | CTRL_CLKSRC;

    for (int i = 0; i < delay; i++)
    {
        /* Wait until the COUNTFLAG is set */
        while ((SysTick->CTRL & CTRL_COUNTFLAG) == 0) {}
    }

    /* Disable SysTick */
    SysTick->CTRL = 0;
}

// =======================
// MAIN FUNCTION
// =======================

#define GPIOAEN    (1U << 0)
#define PIN5       (1U << 5)
#define LED        PIN5

int main(void)
{
    /* 1. Enable clock access to GPIOA */
    RCC->AHB1ENR |= GPIOAEN;

    /* 2. Set PA5 as output pin */
    GPIOA->MODER |= (1U << 10);
    GPIOA->MODER &= ~(1U << 11);

    uart2_tx_init();

    while (1)
    {
        printf("A second passed !! \n\r");
        GPIOA->ODR ^= LED;
        systickDelayMs(1000);
    }
}
