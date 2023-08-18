/*
 * ssc_bsp.h
 *
 *  Created on: 2023年8月12日
 *      Author: maxiu
 */

#ifndef INC_SSC_BSP_H_
#define INC_SSC_BSP_H_

#include	<stdint.h>

#include	<cmsis_gcc.h>
#define		ENABLE_GLOBAL_INT		__enable_irq()
#define		DISABLE_GLOBAL_INT		__disable_irq()

#define		ENABLE_AL_EVENT_INT		ENABLE_GLOBAL_INT
#define		DISABLE_AL_EVENT_INT	DISABLE_GLOBAL_INT

/**
 * select & deselect esc SPI  NSS pin reset & set
 */
void	spi_Select	(void);
void	spi_Deselect(void);
#define		SELECT_SPI				spi_Select();
#define		DESELECT_SPI			spi_Deselect();

/**
 *	enable & disable PDI_IRQ, SYNC0, SYNC1 interrupt
 */
void	al_Event_Int_Enable	(void);
void	al_Event_Int_Disable(void);

/**
 * Timer6 ESC-tim start & stop IT mode
 */
void	timer_Esc_IT_Start	(void);
void	timer_Esc_IT_Stop	(void);
#define	START_ECAT_TIMER	timer_Esc_IT_Start()
/**
 * Enable & Disable ESC INT, SYNC0, SYNC1, tim
 */
void	enable_Irq_Sync0_Sync1	(void);
void	disable_Irq_Sync0_Sync1	(void);
#define	ENABLE_ESC_INT()	enable_Irq_Sync0_Sync1()
#define	DISABLE_ESC_INT()	disable_Irq_Sync0_Sync1()
/**
 * Timer6 counter value get
 */
uint32_t	timer_Get_Value	(void);
#define	HW_GetTimer()	(timer_Get_Value())

#endif /* INC_SSC_BSP_H_ */
