
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

unsigned long micros()
{
    return count;
}
unsigned int TimingDelay;

void Delay(unsigned int nTime)
{
    TimingDelay = nTime;
    while (TimingDelay != 0)
        ;
}

void TimingDelay_Decrement(void)
{
    if (TimingDelay != 0x00) {
        TimingDelay--;
    }
}

void SysTick_Handler(void)
{
    TimingDelay_Decrement();
    count++;
}

void column(char data)
{

    char tmp = 0x00;

    for (i = 0; i < 8; i++) {
        if (data & (0x80 >> i)) {
            tmp += pow(2, i);
        }
    }
    GPIOC->ODR = ~tmp;
}

void row(char data)
{
    GPIOB->ODR = (0x01 << 8) << data;
}

char num[10][8] = {
    { 0x00, 0x38, 0x44, 0x4c, 0x54, 0x64, 0x44, 0x38 },
    { 0x00, 0x10, 0x30, 0x50, 0x10, 0x10, 0x10, 0x7c },
    { 0x00, 0x38, 0x44, 0x04, 0x08, 0x10, 0x20, 0x7c },
    { 0x00, 0x38, 0x44, 0x04, 0x18, 0x04, 0x44, 0x38 },
    { 0x00, 0x08, 0x18, 0x28, 0x48, 0x7c, 0x08, 0x08 },
    { 0x00, 0x7c, 0x40, 0x78, 0x04, 0x04, 0x44, 0x38 },
    { 0x00, 0x38, 0x40, 0x40, 0x78, 0x44, 0x44, 0x38 },
    { 0x00, 0x7c, 0x04, 0x08, 0x10, 0x20, 0x20, 0x20 },
    { 0x00, 0x38, 0x44, 0x44, 0x38, 0x44, 0x44, 0x38 },
    { 0x00, 0x38, 0x44, 0x44, 0x3c, 0x04, 0x44, 0x38 }
};
int line = 0;
int col_cnt = 0;
int tmp2;

int duty[8][8] = {

    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 10, 20, 30, 40, 50, 60, 70, 80 },
    { 10, 10, 10, 10, 10, 10, 10, 40 },
    { 10, 10, 10, 10, 10, 10, 10, 40 },
    { 10, 10, 10, 10, 10, 10, 10, 10 },
    { 10, 10, 10, 10, 10, 10, 10, 10 },
    { 10, 10, 10, 10, 10, 10, 10, 10 },
    { 10, 10, 10, 10, 10, 10, 10, 10 },
};

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

void TIM2_IRQHandler(void)
{

    if ((TIM2->SR & 0x0001) != 0) { // check interrupt source
			
			SPI1->DR = (~num[3][line] << 8) | (0x80>>line);
			GPIOC->ODR = 0x04;
			//Delay(1);
			GPIOC->ODR = 0x00;

        line++;
        if (line == 8) {
            line = 0;
        }

        TIM2->SR &= ~(1 << 0); // clear UIF flag
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

int main(void)
{

    stm32_Init(); // STM32 setup
    RCC->APB1ENR = 0x01;
    RCC->APB2ENR = 0x1014;
    GPIOC->CRL = 0x33333333;
    SysTick->CTRL = 0x00000007;
    SysTick->LOAD = 0x000002D0;
	  TIM2->ARR = 100;
    TIM2->PSC = 720;
    TIM2->CR1 = 0x01;
    TIM2->DIER = 0x01;
    NVIC->ISER[0] = 0x10000000;
	SPI1->CR1 = 0x0B6C;
	SPI1->SR = 0X02;

    for (;;) {

        //        c_micors = micros();

        //        if (c_micors - p_micors1 > 10) {

        //            p_micors1 = c_micors;

        //            col_cnt++;
        //            if (col_cnt == 10) {
        //                col_cnt = 0;
        //                row( 7 - line);
        //                line++;
        //								tmp2 = 0xff;
        //                if (line == 8){
        //                    line = 0;
        //								}
        //            }
        //
        //												for(i = 0;i < 8; i++){
        //							if(duty[line][i] == col_cnt){
        //								tmp2 &= ~(0x80>>i);
        //							}
        //						}
        //						column(tmp2);
        //
        //
        //        }
        //
        //
    }
}
