

/**
  ******************************************************************************
  * @file    GPIO/IOToggle/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body. 
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

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

static __IO uint32_t TimingDelay;

/* Private function prototypes -----------------------------------------------*/
void Delay(__IO uint32_t nTime);
//#include "stm32_eval.h"

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
GPIO_InitTypeDef GPIO_InitStructure;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
	
	void Delay(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}

	
	int j , i;
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */     

#ifdef IOTOGGLE_BOARD       
  /* GPIOD Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
#else
  /* GPIOD Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

  /* Configure PD0 and PD2 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
#endif


  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  while(1){
		
			GPIOA->BSRR = 0x01<<5;
		Delay(10000);
					GPIOA->BRR = 0x01<<5;
		Delay(10000);


	}


  /* To achieve GPIO toggling maximum frequency, the following  sequence is mandatory. 
     You can monitor PD0 or PD2 on the scope to measure the output signal. 
     If you need to fine tune this frequency, you can add more GPIO set/reset 
     cycles to minimize more the infinite loop timing.
     This code needs to be compiled with high speed optimization option.  */
  while (1)
  {
  	unsigned int i,j;

#ifdef IOTOGGLE_BOARD       
    /* Set PD0 and PD2 */
    GPIOA->BSRR = 0x00000100;
    GPIOB->BSRR = 0x00008000;
#else
    /* Set PD0 and PD2 */
    GPIOD->BSRR = 0x00000005;
#endif

	//delay(100);
		// 0.5 sec delay
	  for(i=0;i<100;i++)
	  	for(j=0;j<60000;j++);

#ifdef IOTOGGLE_BOARD       
    /* Reset PD0 and PD2 */
    GPIOA->BRR  = 0x00000100;
    GPIOB->BRR  = 0x00008000;
#else
    /* Reset PD0 and PD2 */
    GPIOD->BRR  = 0x00000005;
#endif

	//delay(100);
		// 0.5 sec delay
	  for(i=0;i<100;i++)
	  	for(j=0;j<60000;j++);


 #if 0
    /* Set PD0 and PD2 */
    GPIOD->BSRR = 0x00000005;
    /* Reset PD0 and PD2 */
    GPIOD->BRR  = 0x00000005;

    /* Set PD0 and PD2 */
    GPIOD->BSRR = 0x00000005;
    /* Reset PD0 and PD2 */
    GPIOD->BRR  = 0x00000005;

    /* Set PD0 and PD2 */
    GPIOD->BSRR = 0x00000005;
    /* Reset PD0 and PD2 */
    GPIOD->BRR  = 0x00000005;

    /* Set PD0 and PD2 */
    GPIOD->BSRR = 0x00000005;
    /* Reset PD0 and PD2 */
    GPIOD->BRR  = 0x00000005;

    /* Set PD0 and PD2 */
    GPIOD->BSRR = 0x00000005;
    /* Reset PD0 and PD2 */
    GPIOD->BRR  = 0x00000005;

    /* Set PD0 and PD2 */
    GPIOD->BSRR = 0x00000005;
    /* Reset PD0 and PD2 */
    GPIOD->BRR  = 0x00000005;

    /* Set PD0 and PD2 */
    GPIOD->BSRR = 0x00000005;
    /* Reset PD0 and PD2 */
    GPIOD->BRR  = 0x00000005;

    /* Set PD0 and PD2 */
    GPIOD->BSRR = 0x00000005;
    /* Reset PD0 and PD2 */
    GPIOD->BRR  = 0x00000005;

    /* Set PD0 and PD2 */
    GPIOD->BSRR = 0x00000005;
    /* Reset PD0 and PD2 */
    GPIOD->BRR  = 0x00000005;
 #endif
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}

#endif

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
