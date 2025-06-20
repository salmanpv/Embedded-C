![image](https://github.com/user-attachments/assets/9e8ab2e6-656d-4e11-999b-d825c4348e0c)

![image](https://github.com/user-attachments/assets/9edb8c62-6c64-4f22-8b2f-8ed465b98b52)

![image](https://github.com/user-attachments/assets/0b014d15-d364-445a-92fa-b1554fb8d2a6)

![image](https://github.com/user-attachments/assets/8e9ba434-8d11-4f53-8661-780c0e948af7)

![image](https://github.com/user-attachments/assets/64eab9f9-26bb-45c4-8b54-080fcf34f9c2)

![image](https://github.com/user-attachments/assets/8f57178f-568d-4192-8f6c-47e3b0a7c5bb)

![image](https://github.com/user-attachments/assets/d58ef8a3-8349-478c-9847-2000d5d9139a)

![image](https://github.com/user-attachments/assets/e252e586-7f89-4c65-a61f-6fcac51686a5)

![image](https://github.com/user-attachments/assets/f6127a10-2e41-4b21-8934-198eb7b72346)

![image](https://github.com/user-attachments/assets/44e1a02b-5848-4b7d-9a68-58eb47ccc977)

![image](https://github.com/user-attachments/assets/5c035b20-c351-4383-a92c-18dacbcc8c26)

![image](https://github.com/user-attachments/assets/f5869db6-b833-4f75-a1e0-41484d6c73d4)

![image](https://github.com/user-attachments/assets/a4c009da-3ccb-4b2b-8d39-d4d1617038e7)

for timer:
![image](https://github.com/user-attachments/assets/b97d765f-8c4c-42c6-b5c0-7536b399abd6)


bitwise note:  

Enable systick and select internal clk src  
SysTick->CTRL = CTRL_ENABLE | CTRL_CLKSRC; 

SysTick->CTRL & CTRL_COUNTFLAG) == 0  

Enable clock access to GPIOA  
RCC->AHB1ENR |= GPIOAEN;  

Set PA5 as output pin  
GPIOA->MODER |= (1U << 10);  
GPIOA->MODER &= ~(1U << 11); 

check update interupt flag  
TIM2 -> SR & 1;

clear update interupt flag  
TIM2 -> SR &= ~1;  







