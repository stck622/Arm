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
int duty = 0;

unsigned long micros() {
    return count;
}
unsigned int TimingDelay;

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

void TIM2_IRQHandler(void) {

    if ((TIM2  -> SR & 0x0001) != 0) {

        TIM2  -> SR &= ~(1 << 0); // clear UIF flag
			timer_count++;
			
			if(timer_count == duty){
				GPIOA->ODR= 0x00;
			}
			
			if(timer_count == 100){
				timer_count = 0;
				GPIOA->ODR = 0x20;
			}
			
    }

    //	if ((TIM2->SR & 0x0002) != 0){
    //		GPIOA->ODR &= ~(0x01 << 5);
    //		TIM2->SR &= ~(1<<1);
    // }
}

unsigned long c_micors, p_micors1, p_micros2;

/*----------------------------------------------------------*\
 | MIAN ENTRY                                               |
\*----------------------------------------------------------*/

int main(void) {

    stm32_Init(); // STM32 setup


    SysTick ->CTRL = 0x00000007;
    SysTick -> LOAD = 0x000002D0;
    RCC -> APB1ENR = 0x01;
    RCC -> APB2ENR = 0x04;
    TIM2 -> DIER = 0x01;
    TIM2 -> CR1 = 0x01;
		GPIOA->CRL = (0x03 << 20);
	
	TIM2->PSC = 0x48;
	TIM2->ARR= 0x64;
    NVIC->ISER[0] = 0x10000000;

    for (;;) {
			
			c_micors = micros();
			
			if(c_micors - p_micors1 > 1000){
				
				p_micors1 = c_micors;
				
				duty++;
				if(duty == 100){
					duty = 0;
				}
			
			}

    }
}