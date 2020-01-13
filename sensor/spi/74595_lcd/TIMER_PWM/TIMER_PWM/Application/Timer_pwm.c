#include <stdio.h>
#include <stm32f10x_lib.h> // STM32F10x Library Definitions
#include "STM32_Init.h" // STM32 Initialization
#include <math.h>
volatile unsigned long count = 0;
unsigned int timer_count = 0;
unsigned int timer_count2 = 0;
int pwm_var = 0;
int flag = 0;
int ledLight = 0;
int ledLight1 = 0;
int ledLight2 = 0;
int ledLight3 = 0;
int i, j, col;
unsigned long micros() {
	return count;
}
unsigned long TimingDelay;
void Delay(unsigned int nTime) {
	TimingDelay = nTime;
	while (TimingDelay != 0)
	        ;
}
void TimingDelay_Decrement(void) {
	if (TimingDelay != 0x00) {
		TimingDelay--;
	}
}
void SysTick_Handler(void) {
	TimingDelay_Decrement();
	count++;
}
/*----------------------------------------------------------*\
 | HARDWARE DEFINE                                          |
\*----------------------------------------------------------*/
//#define LED             ( 1 << 5 )                // PB5: LED D2
#define LED (1 << 6) // PB5: LED D2
#define LED1 (1 << 7) // PB5: LED D2
#define LED2 (1 << 8) // PB5: LED D2
/*----------------------------------------------------------*\
 | Timer1 Update Interrupt Handler                          |
\*----------------------------------------------------------*/
//void TIM1_UP_IRQHandler (void) {
//  if ((TIM1->SR & 0x0001) != 0) {                 // check interrupt source
//////	ledLight = ~ledLight;
//////	if( ledLight )
//////    	GPIOC->ODR &= ~(0x01 << 13);                           // switch on LED
//////	else
//////    	GPIOC->ODR |=  0x01 << 13;                           // switch off LED
////
////		GPIOA->ODR |=   (0x01 << 5);
//////
//////		GPIOC->ODR |= 0x01 << 13;
//////
//    TIM1->SR &= ~(1<<0);                          // clear UIF flag
////
// }
//} // end TIM1_UP_IRQHandler
//void TIM1_CC_IRQHandler (void) {
//  if ((TIM1->SR & 0x0002) != 0) {                 // check interrupt source
////	ledLight = ~ledLight;
////	if( ledLight )
////    	GPIOC->ODR &= ~(0x01 << 13);                           // switch on LED
////	else
////    	GPIOB->ODR |=  LED;                           // switch off LED
//GPIOA->ODR &= ~(0x01 << 5);
//    TIM1->SR &= ~(1<<1);                          // clear UIF flag
// }
//} // end TIM1_UP_IRQHandler
///*----------------------------------------------------------*\
//                        |
//\*----------------------------------------------------------*/
unsigned long c_micors, p_micors1, p_micros2;
/*----------------------------------------------------------*\
 | MIAN ENTRY                                               |
\*----------------------------------------------------------*/
void lcd_en() {
	GPIOC->ODR = 0x04;
	Delay(5);
	GPIOC->ODR = 0x00;
}
void spi_send_data(char a) {
	SPI1->DR = a;
	while(!(SPI1->SR & 0x02));
	Delay(5);
	lcd_en();
}
void lcd_send_cmd(int cmd) {
	spi_send_data(0x00);
	spi_send_data(0x00 | cmd);
	spi_send_data(0x00 | cmd | 0x04);
	spi_send_data(0x00 | cmd);
	spi_send_data(0x00 | 0x01);
	Delay(5);
}
void lcd_send_data(int data) {
	spi_send_data(0x01);
	spi_send_data(0x01 | data);
	spi_send_data(0x01 | data | 0x04);
	spi_send_data(0x01 | data);
	spi_send_data(0x01);
	Delay(5);
}
int main(void) {
	stm32_Init();
	// STM32 setup
	
	RCC->APB1ENR = 0x01;
	RCC->APB2ENR = 0x1014;
	GPIOC->CRL = 0x33333333;
	SysTick->CTRL = 0x00000007;
	SysTick->LOAD = 0x000002D0;
	NVIC->ISER[0] = 0x10000000;
	SPI1->CR1 = 0x037C;
	SPI1->SR = 0X02;
	Delay(100);
	
	lcd_send_cmd(0x30);
	lcd_send_cmd(0x30);
	lcd_send_cmd(0x30);
	lcd_send_cmd(0x20);
	lcd_send_cmd(0x20);
	lcd_send_cmd(0x80);
	lcd_send_cmd(0x00);
	lcd_send_cmd(0x60);
	lcd_send_cmd(0x00);
	lcd_send_cmd(0xC0);
	lcd_send_cmd(0x80);
	lcd_send_cmd(0x00);
	lcd_send_cmd(0x00);
	lcd_send_cmd(0x10);
	Delay(5);
	for (;;) {
		lcd_send_data(0x30);
		lcd_send_data(0x10);
		Delay(100000);
	}
}