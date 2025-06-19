#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"

/* Definitions */
#define GPIOAEN     (1U << 0)
#define PIN5        (1U << 5)
#define LED         PIN5

#define TIM2EN      (1U << 0)
#define CR1_CEN     (1U << 0)
#define SR_UIF      (1U << 0)

/* Function Prototypes */
void tim2_1hz_init(void);
void uart2_tx_init(void);  // Assuming you have uart2_tx_init defined elsewhere.

/* Timer Initialization */
void tim2_1hz_init(void)
{
    /* Enable clock access to TIM2 */
    RCC->APB1ENR |= TIM2EN;

    /* Set prescaler value */
    TIM2->PSC = 1600 - 1;  // 16 MHz / 1600 = 10 kHz

    /* Set auto-reload value */
    TIM2->ARR = 10000 - 1; // 10 kHz / 10,000 = 1 Hz (1 second)

    /* Clear counter */
    TIM2->CNT = 0;

    /* Enable timer */
    TIM2->CR1 = CR1_CEN;
}

int main(void)
{
    /* Enable clock access to GPIOA */
    RCC->AHB1ENR |= GPIOAEN;

    /* Set PA5 as output pin */
    GPIOA->MODER |= (1U << 10);
    GPIOA->MODER &= ~(1U << 11);

    uart2_tx_init();  // UART init assumed to be defined elsewhere
    tim2_1hz_init();

    while (1)
    {
        /* Wait for UIF flag */
        while (!(TIM2->SR & SR_UIF)) {}

        /* Clear UIF flag */
        TIM2->SR &= ~SR_UIF;

        printf("A second passed!! \n\r");

        /* Toggle LED on PA5 */
        GPIOA->ODR ^= LED;
    }
}
