/*****************************************************************************
*                    Q u a n t u m     L e a P s
*                    ---------------------------
*                    innovating embedded systems
*
* Copyright (C) 2002-2012 Quantum Leaps, LLC. All rights reserved.
*
*****************************************************************************/
#include "qpc.h"
#include "bsp.h"
#include "hw_config.h"
#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "usart.h"

void Q_onAssert(char const Q_ROM * const Q_ROM_VAR file, int line) 
{
	
}

/* QF callbacks ============================================================*/
void QF_onStartup(void) {
    /* set up the SysTick timer to fire at BSP_TICKS_PER_SEC rate */
    SysTick_Config(SystemCoreClock / BSP_TICKS_PER_SEC);

    /* assing all priority bits for preemption-prio. and none to sub-prio. */
    NVIC_SetPriorityGrouping(0U);

    /* set priorities of ALL ISRs used in the system, see NOTE00
    *
    * !!!!!!!!!!!!!!!!!!!!!!!!!!!! CAUTION !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    * Assign a priority to EVERY ISR explicitly by calling NVIC_SetPriority().
    * DO NOT LEAVE THE ISR PRIORITIES AT THE DEFAULT VALUE!
    */
    //NVIC_SetPriority(USART2_IRQn,    USART2_PRIO);
    //NVIC_SetPriority(SysTick_IRQn,   SYSTICK_PRIO);
    /* ... */

    /* enable IRQs... */
#ifdef Q_SPY
    NVIC_EnableIRQ(USART2_IRQn); /* USART2 interrupt used for QS-RX */
#endif
}

//空闲时进入低功耗模式
void QF_onIdle(void) 
{
#ifdef NDEBUG
	/* put the CPU and peripherals to the low-power mode, see NOTE02 */
	__WFI();
#endif
	QF_INT_ENABLE();                            /* always enable interrupts */
}

void QF_onCleanup(void) 
{

}

void QF_onClockTick(void) 
{
	QF_TICK((void *)0);
}

/* ISRs used in this project ===============================================*/
void SysTick_Handler(void) 
{
	//printf("systick\n");
	
#ifdef Q_SPY
    {
        tmp = SysTick->CTRL; /* clear SysTick_CTRL_COUNTFLAG */
        QS_tickTime_ += QS_tickPeriod_; /* account for the clock rollover */
    }
#endif

    QF_TICK_X(0U, &l_SysTick);
}

/*..........................................................................*/
void BSP_init(void) {
	System_Init();		//系统初始化函数，定义在hw_config.c
}

/*..........................................................................*/
void BSP_led1_Off(void) {
	GPIOA->BSRR = GPIO_Pin_8;
}

/*..........................................................................*/
void BSP_led1_On(void) {
	GPIOA->BRR = GPIO_Pin_8;
}

/*..........................................................................*/
void BSP_led2_Off(void) {
	GPIOD->BSRR = GPIO_Pin_2;
}

/*..........................................................................*/
void BSP_led2_On(void) {
	GPIOD->BRR = GPIO_Pin_2;
}
