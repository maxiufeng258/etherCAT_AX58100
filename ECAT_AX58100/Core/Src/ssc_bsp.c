/*
 * ssc_bsp.c
 *
 *  Created on: 2023年8月12日
 *      Author: maxiu
 */

#include	<ssc_bsp.h>


#include	<gpio.h>

extern	void EscIsr(void);
extern	void Sync0Isr(void);
extern	void Sync1Isr(void);

extern	void ECAT_CheckTimer(void);	/** from <ecatappl.c> */

uint8_t userBtn1Bit = 0;

/**
 * select esc SPI  NSS pin reset
 */
void	spi_Select	(void)
{
	HAL_GPIO_WritePin(SPI3_NSS_GPIO_Port, SPI3_NSS_Pin, GPIO_PIN_RESET);
}

/**
 * deselect esc SPI  NSS pin set
 */
void	spi_Deselect(void)
{
	HAL_GPIO_WritePin(SPI3_NSS_GPIO_Port, SPI3_NSS_Pin, GPIO_PIN_SET);
}


/**
 *	enable PDI_IRQ, SYNC0, SYNC1 interrupt
 */
void	al_Event_Int_Enable	(void)
{
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}

/**
 * disable PDI_IRQ, SYNC0, SYNC1 interrupt
 */
void	al_Event_Int_Disable(void)
{
	HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
}


/**TIM_HandleTypeDef htim6; from <tim.c> */
extern	TIM_HandleTypeDef htim6;
/**
 * Timer6 ESC-tim start IT mode
 */
void	timer_Esc_IT_Start	(void)
{
	HAL_TIM_Base_Start_IT(&htim6);
}

/**
 * Timer6 ESC-tim stop  IT mode
 */
void	timer_Esc_IT_Stop	(void)
{
	HAL_TIM_Base_Stop_IT(&htim6);
}

/**
 * Timer6 counter value get
 */
uint32_t	timer_Get_Value	(void)
{
	return	__HAL_TIM_GET_COUNTER(&htim6);
}


/**
 * Enable ESC INT, SYNC0, SYNC1
 */
void	enable_Irq_Sync0_Sync1	(void)
{
	al_Event_Int_Enable();
}

/**
 * Disable ESC INT, SYNC0, SYNC1
 */
void	disable_Irq_Sync0_Sync1	(void)
{
	al_Event_Int_Disable();
}


/**
 * ESC related PDI_IRQ, SYNC0, SYNC1 interrupt callback
 * and others interrupt callback can be add to here
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	// timer6 used esc timer 1ms
	if (htim->Instance == htim6.Instance)
	{
		/** from <el9800w.c> */
		ECAT_CheckTimer();
		static	int cnt = 0;
		if (200 == cnt)
		{
			cnt = 0;
//			HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
		}
		cnt++;

	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	/** handler PDI_IRQ interrupt */
	if (PDI_IRQ_Pin == GPIO_Pin)
	{
		/** from <el9800w.c> */
		EscIsr();
		static int cntIrq = 0;
		if (cntIrq == 500)
		{
//			HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
			cntIrq = 0;
		}
		cntIrq++;
	}
	/** handler SYNC0 interrupt */
	if (sync0_Pin == GPIO_Pin)
	{
		/** from <el9800w.c> */
		Sync0Isr();
//		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	}
	/** handler SYNC1 interrupt */
	if (sync1_Pin == GPIO_Pin)
	{
		/** from <el9800w.c> */
		Sync1Isr();
	}

	/** handler User BTB interrupt */
	if (USER_Btn_Pin == GPIO_Pin)
	{
//		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		int cntBtn = 0;
		for (cntBtn = 2000; cntBtn > 0; cntBtn--);
		if (HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin))
			userBtn1Bit = !userBtn1Bit;
	}
}



