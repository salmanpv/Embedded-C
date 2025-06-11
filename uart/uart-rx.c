#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"

/* Macros for peripheral configuration */
#define GPIOAEN       (1U<<0)
#define UART2EN       (1U<<17)

#define CR1_TE        (1U<<3)
#define CR1_RE        (1U<<2)
#define CR1_UE        (1U<<13)

#define SR_TXE        (1U<<7)
#define SR_RXNE       (1U<<5)

#define GPIOA_5       (1U<<5)
#define LED_PIN       GPIOA_5

#define SYS_FREQ      16000000
#define APB1_CLK      SYS_FREQ
#define UART_BAUDRATE 115200

/* Function Prototypes */
void uart2_rxtx_init(void);
void uart2_write(int ch);
char uart2_read(void);
static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);

/* Redirect printf to UART */
int __io_putchar(int ch)
{
    uart2_write(ch);
    return ch;
}

int main(void)
{
    char key;

    /* Enable clock access to GPIOA */
    RCC->AHB1ENR |= GPIOAEN;

    /* Set PA5 as output pin */
    GPIOA->MODER |= (1U<<10);
    GPIOA->MODER &= ~(1U<<11);

    /* Initialize UART for TX and RX */
    uart2_rxtx_init();

    while(1)
    {
        key = uart2_read();

        if (key == '1')
        {
            GPIOA->ODR |= LED_PIN;   // Turn on LED
        }
        else
        {
            GPIOA->ODR &= ~LED_PIN;  // Turn off LED
        }

        printf("Received: %c\n\r", key);  // Optional feedback
    }
}

void uart2_rxtx_init(void)
{
    /* Enable clock access to GPIOA */
    RCC->AHB1ENR |= GPIOAEN;

    /* Set PA2 mode to alternate function mode (TX) */
    GPIOA->MODER &= ~(1U<<4);
    GPIOA->MODER |= (1U<<5);

    /* Set PA2 alternate function type to UART_TX (AF07) */
    GPIOA->AFR[0] |= (1U<<8) | (1U<<9) | (1U<<10);
    GPIOA->AFR[0] &= ~(1U<<11);

    /* Set PA3 mode to alternate function mode (RX) */
    GPIOA->MODER &= ~(1U<<6);
    GPIOA->MODER |= (1U<<7);

    /* Set PA3 alternate function type to UART_RX (AF07) */
    GPIOA->AFR[0] |= (1U<<12) | (1U<<13) | (1U<<14);
    GPIOA->AFR[0] &= ~(1U<<15);

    /* Enable clock access to UART2 */
    RCC->APB1ENR |= UART2EN;

    /* Configure baudrate */
    uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

    /* Configure transfer direction: TX and RX */
    USART2->CR1 = (CR1_TE | CR1_RE);

    /* Enable UART module */
    USART2->CR1 |= CR1_UE;
}

void uart2_write(int ch)
{
    // You wait until the Transmit Data Register is empty before you write new data.
    // If the register is still holding the previous data (still being sent), you must wait.
    /* Wait until transmit data register is empty */
    while (!(USART2->SR & SR_TXE)) {}

    /* Write to transmit data register */
    USART2->DR = (ch & 0xFF);
}

char uart2_read(void)
{
    // Waits until data is available to read.  
    // If you skip this check and read immediately, you might read garbage or read before new data has arrived.  
    /* Wait until receive data register is not empty */
    while (!(USART2->SR & SR_RXNE)) {}

    /* Read received data */
    return USART2->DR;
}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate)
{
    USARTx->BRR = compute_uart_bd(PeriphClk, BaudRate);
}

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate)
{
    return (PeriphClk + (BaudRate / 2U)) / BaudRate;
}
