

/**
  ******************************************************************************
  * @file	 GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date	 08-April-2011
  * @brief	 Main Interrupt Service Routines.
  * 		 This file provides template for all exceptions handler and peripherals
  * 		 interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */
#include "stm32f10x_it.h"

/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup GPIO_IOToggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*			  Cortex-M3 Processor Exceptions Handlers						  */
/******************************************************************************/

/**
  * @brief	This function handles NMI exception.
  * @param	None
  * @retval None
  */
void NMI_Handler(void)
{
}


/**
  * @brief	This function handles Hard Fault exception.
  * @param	None
  * @retval None
  */
void HardFault_Handler(void)
{
	/* Go to infinite loop when Hard Fault exception occurs */
	while (1)
		{
		}
}


/**
  * @brief	This function handles Memory Manage exception.
  * @param	None
  * @retval None
  */
void MemManage_Handler(void)
{
	/* Go to infinite loop when Memory Manage exception occurs */
	while (1)
		{
		}
}


/**
  * @brief	This function handles Bus Fault exception.
  * @param	None
  * @retval None
  */
void BusFault_Handler(void)
{
	/* Go to infinite loop when Bus Fault exception occurs */
	while (1)
		{
		}
}


/**
  * @brief	This function handles Usage Fault exception.
  * @param	None
  * @retval None
  */
void UsageFault_Handler(void)
{
	/* Go to infinite loop when Usage Fault exception occurs */
	while (1)
		{
		}
}


/**
  * @brief	This function handles SVCall exception.
  * @param	None
  * @retval None
  */
void SVC_Handler(void)
{
}


/**
  * @brief	This function handles Debug Monitor exception.
  * @param	None
  * @retval None
  */
void DebugMon_Handler(void)
{
}


/**
  * @brief	This function handles PendSV_Handler exception.
  * @param	None
  * @retval None
  */
void PendSV_Handler(void)
{
}


/**
  * @brief	This function handles SysTick Handler.
  * @param	None
  * @retval None
  */
static __IO uint32_t TimingDelay;
volatile unsigned long micros_count = 0;


void Delay(__IO uint32_t nTime)
{
	TimingDelay 		= nTime;

	while (TimingDelay != 0)
		;
}



void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
		{
		TimingDelay--;
		}
}



void SysTick_Handler(void)
{
	micros_count++;
	TimingDelay_Decrement();
}


unsigned long micros_10us()
{
	return micros_count;
}


void led_toggle();
int 			ledLight;

int distance_flag;


void TIM2_IRQHandler(void)
{

	if ((TIM2->SR & 0x0001) != 0)
		{ // check interrupt source
			
			if(distance_flag){
			
			if((ledLight = !ledLight)){
								GPIOA->BRR = 0x01<<7; 
			} else {
			GPIOA->BSRR = 0x01<<7; 
			}

		//	led_toggle();
		TIM2->SR			&= ~(1 << 0);			// clear UIF flag
		}
	} else {
	
		GPIOA->BRR = 0x01<<7; 
	
	}

	//	if ((TIM2->SR & 0x0002) != 0){
	//		GPIOA->ODR &= ~(0x01 << 5);
	//		TIM2->SR &= ~(1<<1);
	// }
}


 double distance;
unsigned long pre,cur;

double get_dis(){
return distance;
}


void EXTI15_10_IRQHandler(void)
{
	if (EXTI->PR & (1 << 10))
		{ // EXTI0 interrupt pending?

		if (GPIOA->IDR & (1 << 10))
			{
			pre = micros_10us();
			}
		else 
			{
				cur = micros_10us() ;
				distance = ((cur-pre)*0.034*10)/2;
			}

		EXTI->PR			= (1 << 10);			// clear pending interrupt
		}
}





/******************************************************************************/
/*				   STM32F10x Peripherals Interrupt Handlers 				  */
/*	Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*	available peripheral interrupt handler's name please refer to the startup */
/*	file (startup_stm32f10x_xx.s).											  */
/******************************************************************************/

/**
  * @brief	This function handles PPP interrupt request.
  * @param	None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
