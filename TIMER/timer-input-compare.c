//used to measure freaquency of input signal

#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"

/* Macros */
#define TIM2EN       (1U << 0)
#define TIM3EN       (1U << 1)

#define CR1_CEN      (1U << 0)
#define OC_TOGGLE    ((1U << 4) | (1U << 5))
#define CCER_CC1E    (1U << 0)

#define GPIOAEN      (1U << 0)
#define AFR5_TIM     (1U << 20)
#define AFR6_TIM     (1U << 25)
#define CCER_CC1S    (1U << 0)

#define SR_UIF       (1U << 0)
#define SR_CC1IF     (1U << 1)

/* Function Prototypes */
void tim2_1hz_init(void);
void tim2_pa5_output_compare(void);
void tim3_pa6_input_capture(void);

/* Global Variable */
int timestamp = 0;

/* Main Program */
int main(void)
{
    /* Configure TIM2 for Output Compare to toggle PA5 */
    tim2_pa5_output_compare();

    /* Configure TIM3 for Input Capture on PA6 */
    tim3_pa6_input_capture();

    while (1)
    {
        /* Wait until edge is captured */
        while (!(TIM3->SR & SR_CC1IF)) {}

        /* Read captured value */
        timestamp = TIM3->CCR1;

        /* (Optional) Clear the interrupt flag (not strictly needed in this polling example) */
        TIM3->SR &= ~SR_CC1IF;
    }
}

/* Timer 2 - Simple 1Hz Timer Initialization (if needed separately) */
void tim2_1hz_init(void)
{
    /* Enable clock access to TIM2 */
    RCC->APB1ENR |= TIM2EN;

    /* Set prescaler value */
    TIM2->PSC = 1600 - 1;  // 16 MHz / 1600 = 10 kHz

    /* Set auto-reload value */
    TIM2->ARR = 10000 - 1; // 10 kHz / 10,000 = 1 Hz

    /* Clear counter */
    TIM2->CNT = 0;

    /* Enable timer */
    TIM2->CR1 = CR1_CEN;
}

/* Timer 2 - Output Compare Toggle on PA5 */
void tim2_pa5_output_compare(void)
{
    /* Enable clock access to GPIOA */
    RCC->AHB1ENR |= GPIOAEN;

    /* Set PA5 mode to alternate function */
    GPIOA->MODER &= ~(1U << 10);
    GPIOA->MODER |=  (1U << 11);

    /* Set PA5 alternate function type to TIM2_CH1 (AF01) */
    GPIOA->AFR[0] |= AFR5_TIM;

    /* Enable clock access to TIM2 */
    RCC->APB1ENR |= TIM2EN;

    /* Set prescaler value */
    TIM2->PSC = 1600 - 1;  // 16 MHz / 1600 = 10 kHz

    /* Set auto-reload value */
    TIM2->ARR = 10000 - 1; // 10 kHz / 10,000 = 1 Hz

    /* Set output compare toggle mode */
    TIM2->CCMR1 = OC_TOGGLE;

    /* Enable TIM2 CH1 in compare mode */
    TIM2->CCER |= CCER_CC1E;

    /* Clear counter */
    TIM2->CNT = 0;

    /* Enable timer */
    TIM2->CR1 = CR1_CEN;
}

/* Timer 3 - Input Capture on PA6 */
void tim3_pa6_input_capture(void)
{
    /* Enable clock access to GPIOA */
    RCC->AHB1ENR |= GPIOAEN;

    /* Set PA6 mode to alternate function */
    GPIOA->MODER &= ~(1U << 12);
    GPIOA->MODER |=  (1U << 13);

    /* Set PA6 alternate function type to TIM3_CH1 (AF02) */
    GPIOA->AFR[0] |= AFR6_TIM;

    /* Enable clock access to TIM3 */
    RCC->APB1ENR |= TIM3EN;

    /* Set prescaler */
    TIM3->PSC = 16000 - 1; // 16 MHz / 16,000 = 1 kHz timer frequency

    /* Set CH1 to input capture */
    TIM3->CCMR1 = CCER_CC1S;

    /* Set CH1 to capture at rising edge */
    TIM3->CCER = CCER_CC1E;

    /* Enable TIM3 */
    TIM3->CR1 = CR1_CEN;
}
