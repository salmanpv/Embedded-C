#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"

/* Macros */
#define TIM2EN		(1U << 0)
#define CR1_CEN		(1U << 0)
#define OC_TOGGLE	((1U << 4) | (1U << 5))
#define CCER_CC1E	(1U << 0)

#define GPIOAEN		(1U << 0)
#define AFR5_TIM	(1U << 20)

#define SR_UIF  	(1U << 0)

/* Function Prototypes */
void tim2_1hz_init(void);
void tim2_pa5_output_compare(void);

/* Timer to Toggle PA5 using Output Compare Mode */
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

/* Simple 1 Hz Timer Initialization (if needed separately) */
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

/* Main Program */
int main(void)
{
	/* Initialize Timer and configure PA5 to toggle at 1 Hz */
	tim2_pa5_output_compare();

	while (1)
	{
		/* Main loop does nothing, PA5 toggles automatically via hardware timer */
	}
}
