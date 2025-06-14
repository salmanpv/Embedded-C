#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"

/* Definitions */
#define GPIOAEN         (1U << 0)
#define ADC1EN          (1U << 8)
#define ADC_CH1         (1U << 0)
#define ADC_SEQ_LEN_1   0x00
#define CR2_AD0N        (1U << 0)
#define CR2_SWSTART     (1U << 30)
#define SR_EOC          (1U << 1)

/* Function Declarations */
void pa1_adc_init(void);
void start_conversion(void);
uint32_t adc_read(void);

/* Global Variable */
uint32_t sensor_value;

int main(void)
{
    uart2_tx_init();      // UART initialization (Assumed to be implemented elsewhere)
    pa1_adc_init();       // Initialize ADC on PA1

    while (1)
    {
        start_conversion();               // Start ADC conversion
        sensor_value = adc_read();        // Read ADC value
        printf("Sensor value : %d \n\r", (int)sensor_value);  // Print sensor value
    }
}

/* ADC Initialization Function */
void pa1_adc_init(void)
{
    /* Enable clock access to GPIOA */
    RCC->AHB1ENR |= GPIOAEN;

    /* Set the mode of PA1 to analog */
    GPIOA->MODER |= (1U << 2);
    GPIOA->MODER |= (1U << 3);

    /* Enable clock access to ADC1 */
    RCC->APB2ENR |= ADC1EN;

    /* Configure conversion sequence start */
    ADC1->SQR3 = ADC_CH1;

    /* Configure conversion sequence length */
    ADC1->SQR1 = ADC_SEQ_LEN_1;

    /* Enable ADC module */
    ADC1->CR2 |= CR2_AD0N;
}

/* Start ADC Conversion */
void start_conversion(void)
{
    ADC1->CR2 |= CR2_SWSTART;
}

/* Read ADC Conversion Result */
uint32_t adc_read(void)
{
    /* Wait for conversion to complete */
    while (!(ADC1->SR & SR_EOC)) {}

    /* Read and return ADC result */
    return (ADC1->DR);
}
