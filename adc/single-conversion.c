#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"

//----------------------- ADC Definitions -----------------------//

#define GPIOAEN         (1U<<0)
#define ADC1EN          (1U<<8)
#define ADC_CH1         (1U<<0)
#define ADC_SEQ_LEN_1   0x00
#define CR2_ADON        (1U<<0)
#define CR2_SWSTART     (1U<<30)
#define SR_EOC          (1U<<1)

//----------------------- UART Definitions -----------------------//

#define GPIOAEN         (1U<<0)
#define UART2EN         (1U<<17)
#define SYS_FREQ        16000000
#define APB1_CLK        SYS_FREQ
#define UART_BAUDRATE   115200

#define CR1_TE          (1U<<3)
#define CR1_UE          (1U<<13)
#define SR_TXE          (1U<<7)

uint32_t sensor_value;

// Function Prototypes
void uart2_tx_init(void);
void uart2_write(int ch);
void pa1_adc_init(void);
void start_conversion(void);
uint32_t adc_read(void);

// Redirect printf to UART
int __io_putchar(int ch)
{
    uart2_write(ch);
    return ch;
}

int main(void)
{
    uart2_tx_init();
    pa1_adc_init();

    while (1)
    {
        start_conversion();
        sensor_value = adc_read();
        printf("Sensor value: %d \n\r", (int)sensor_value);
    }
}

//----------------------- UART Functions -----------------------//

void uart2_tx_init(void)
{
    // Enable clock for GPIOA
    RCC->AHB1ENR |= GPIOAEN;

    // Set PA2 to alternate function mode
    GPIOA->MODER &= ~(1U << 4);
    GPIOA->MODER |= (1U << 5);

    // Set PA2 alternate function type to UART2 (AF07)
    GPIOA->AFR[0] |= (7U << 8);

    // Enable clock access to UART2
    RCC->APB1ENR |= UART2EN;

    // Configure baud rate
    USART2->BRR = APB1_CLK / UART_BAUDRATE;

    // Enable transmitter
    USART2->CR1 = CR1_TE;

    // Enable UART module
    USART2->CR1 |= CR1_UE;
}

void uart2_write(int ch)
{
    // Wait until transmit data register is empty
    while (!(USART2->SR & SR_TXE)) {}

    // Write to transmit data register
    USART2->DR = (ch & 0xFF);
}

//----------------------- ADC Functions -----------------------//

void pa1_adc_init(void)
{
    // Enable clock access to GPIOA
    RCC->AHB1ENR |= GPIOAEN;

    // Set PA1 to analog mode
    GPIOA->MODER |= (1U << 2);
    GPIOA->MODER |= (1U << 3);

    // Enable clock access to ADC1
    RCC->APB2ENR |= ADC1EN;

    // Set conversion sequence start (Channel 1)
    ADC1->SQR3 = ADC_CH1;

    // Conversion sequence length
    ADC1->SQR1 = ADC_SEQ_LEN_1;

    // Enable ADC1
    ADC1->CR2 |= CR2_ADON;
}

void start_conversion(void)
{
    // Start ADC conversion
    ADC1->CR2 |= CR2_SWSTART;
}

uint32_t adc_read(void)
{
    // Wait for conversion to be complete
    while (!(ADC1->SR & SR_EOC)) {}

    // Read converted result
    return (ADC1->DR);
}
