/**
\addtogroup EL9800_HW EL9800 Platform (Serial ESC Access)
@{
*/

/**
\file    el9800hw.c
\author EthercatSSC@beckhoff.com
\brief Implementation
Hardware access implementation for EL9800 onboard PIC18/PIC24 connected via SPI to ESC

\version 5.11

<br>Changes to version V5.10:<br>
V5.11 ECAT10: change PROTO handling to prevent compiler errors<br>
V5.11 EL9800 2: change PDI access test to 32Bit ESC access and reset AL Event mask after test even if AL Event is not enabled<br>
<br>Changes to version V5.01:<br>
V5.10 ESC5: Add missing swapping<br>
V5.10 HW3: Sync1 Isr added<br>
V5.10 HW4: Add volatile directive for direct ESC DWORD/WORD/BYTE access<br>
           Add missing swapping in mcihw.c<br>
           Add "volatile" directive vor dummy variables in enable and disable SyncManger functions<br>
           Add missing swapping in EL9800hw files<br>
<br>Changes to version V5.0:<br>
V5.01 HW1: Invalid ESC access function was used<br>
<br>Changes to version V4.40:<br>
V5.0 ESC4: Save SM disable/Enable. Operation may be pending due to frame handling.<br>
<br>Changes to version V4.30:<br>
V4.40 : File renamed from spihw.c to el9800hw.c<br>
<br>Changes to version V4.20:<br>
V4.30 ESM: if mailbox Syncmanger is disabled and bMbxRunning is true the SyncManger settings need to be revalidate<br>
V4.30 EL9800: EL9800_x hardware initialization is moved to el9800.c<br>
V4.30 SYNC: change synchronisation control function. Add usage of 0x1C32:12 [SM missed counter].<br>
Calculate bus cycle time (0x1C32:02 ; 0x1C33:02) CalcSMCycleTime()<br>
V4.30 PDO: rename PDO specific functions (COE_xxMapping -> PDO_xxMapping and COE_Application -> ECAT_Application)<br>
V4.30 ESC: change requested address in GetInterruptRegister() to prevent acknowledge events.<br>
(e.g. reading an SM config register acknowledge SM change event)<br>
GENERIC: renamed several variables to identify used SPI if multiple interfaces are available<br>
V4.20 MBX 1: Add Mailbox queue support<br>
V4.20 SPI 1: include SPI RxBuffer dummy read<br>
V4.20 DC 1: Add Sync0 Handling<br>
V4.20 PIC24: Add EL9800_4 (PIC24) required source code<br>
V4.08 ECAT 3: The AlStatusCode is changed as parameter of the function AL_ControlInd<br>
<br>Changes to version V4.02:<br>
V4.03 SPI 1: In ISR_GetInterruptRegister the NOP-command should be used.<br>
<br>Changes to version V4.01:<br>
V4.02 SPI 1: In HW_OutputMapping the variable u16OldTimer shall not be set,<br>
             otherwise the watchdog might exceed too early.<br>
<br>Changes to version V4.00:<br>
V4.01 SPI 1: DI and DO were changed (DI is now an input for the uC, DO is now an output for the uC)<br>
V4.01 SPI 2: The SPI has to operate with Late-Sample = FALSE on the Eva-Board<br>
<br>Changes to version V3.20:<br>
V4.00 ECAT 1: The handling of the Sync Manager Parameter was included according to<br>
              the EtherCAT Guidelines and Protocol Enhancements Specification<br>
V4.00 APPL 1: The watchdog checking should be done by a microcontroller<br>
                 timer because the watchdog trigger of the ESC will be reset too<br>
                 if only a part of the sync manager data is written<br>
V4.00 APPL 4: The EEPROM access through the ESC is added

*/


/*--------------------------------------------------------------------------------------
------
------    Includes
------
--------------------------------------------------------------------------------------*/
#include "ecat_def.h"

#include "ecatslv.h"

#define    _EL9800HW_ 1
#include "el9800hw.h"
#undef    _EL9800HW_
/* ECATCHANGE_START(V5.11) ECAT10*/
/*remove definition of _EL9800HW_ (#ifdef is used in el9800hw.h)*/
/* ECATCHANGE_END(V5.11) ECAT10*/

#include "ecatappl.h"


/*--------------------------------------------------------------------------------------
------
------    internal Types and Defines
------
--------------------------------------------------------------------------------------*/

typedef union
{
    unsigned short    Word;
    unsigned char    Byte[2];
} UBYTETOWORD;

typedef union 
{
    UINT8           Byte[2];
    UINT16          Word;
}
UALEVENT;

/*-----------------------------------------------------------------------------------------
------
------    SPI defines/macros
------
-----------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------
------
------    Global Interrupt setting
------
-----------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------
------
------    ESC Interrupt
------
-----------------------------------------------------------------------------------------*/



/*-----------------------------------------------------------------------------------------
------
------    SYNC0 Interrupt
------
-----------------------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------------------
------
------    Hardware timer
------
-----------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------
------
------    Configuration Bits
------
-----------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------
------
------    LED defines
------
-----------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------
------
------    internal Variables
------
--------------------------------------------------------------------------------------*/
UALEVENT         EscALEvent;            //contains the content of the ALEvent register (0x220), this variable is updated on each Access to the Esc

/*--------------------------------------------------------------------------------------
------
------    internal functions
------
--------------------------------------------------------------------------------------*/

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \brief  The function operates a SPI access without addressing.

        The first two bytes of an access to the EtherCAT ASIC always deliver the AL_Event register (0x220).
        It will be saved in the global "EscALEvent"
*////////////////////////////////////////////////////////////////////////////////////////
static void GetInterruptRegister(void)
{
    UINT8            EscMbxReadEcatCtrl;
    DISABLE_AL_EVENT_INT;
    /* select the SPI */
    SELECT_SPI;

    /* reset transmission flag */
    SPI1_IF=0;

    /* there have to be at least 15 ns after the SPI1_SEL signal was active (0) before
       the transmission shall be started */
    /* write to SPI1_BUF register starts the SPI access*/
    SPI1_BUF = (UINT8) (0x0000 >> 5);

    /* SPI is busy */
    WAIT_SPI_IF

    /* get first byte of AL Event register */

    EscALEvent.Byte[0] = SPI1_BUF;

    /* reset SPI interrupt flag */
    SPI1_IF = 0;

    /* write to SPI1_BUF register starts the SPI access
       read the sm mailbox read ecatenable byte */
    SPI1_BUF = (UINT8) (((0x0000 & 0x1F) << 3) | ESC_RD);
    /* write to SPI1_BUF register starts the SPI access */

    WAIT_SPI_IF
    /* get first byte of AL Event register */

    EscALEvent.Byte[1] = SPI1_BUF;

    /* reset SPI interrupt flag */
    SPI1_IF = 0;
    /* if the SPI transmission rate is higher than 15 MBaud, the Busy detection shall be
       done here */

    /* write to SPI1_BUF register starts the SPI access
       read the sm mailbox read ecatenable byte (last byte) */
    SPI1_BUF = 0xFF;
    /* write to SPI1_BUF register starts the SPI access */
    WAIT_SPI_IF
    /* get first byte of AL Event register */
    EscMbxReadEcatCtrl = SPI1_BUF;
    /* reset SPI interrupt flag */
    SPI1_IF = 0;
    /* there has to be at least 15 ns + CLK/2 after the transmission is finished
       before the SPI1_SEL signal shall be 1 */

    DESELECT_SPI

    ENABLE_AL_EVENT_INT;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \brief  The function operates a SPI access without addressing.
        Shall be implemented if interrupts are supported else this function is equal to "GetInterruptRegsiter()"

        The first two bytes of an access to the EtherCAT ASIC always deliver the AL_Event register (0x220).
        It will be saved in the global "EscALEvent"
*////////////////////////////////////////////////////////////////////////////////////////
static void ISR_GetInterruptRegister(void)
{
    /* SPI should be deactivated to interrupt a possible transmission */
    DESELECT_SPI

    /* select the SPI */
    SELECT_SPI;
    /* reset transmission flag */
    SPI1_IF=0;

    /* there have to be at least 15 ns after the SPI1_SEL signal was active (0) before
       the transmission shall be started */
    /* write to SPI1_BUF register starts the SPI access,
       read the sm mailbox read ecatenable byte
       (has to be synchronous to the al event flags) */
    SPI1_BUF = 0;
    /* SPI is busy */
    WAIT_SPI_IF

    /* get first byte of AL Event register */
    EscALEvent.Byte[0] = SPI1_BUF;
    /* reset SPI interrupt flag */
    SPI1_IF = 0;

    /* write to SPI1_BUF register starts the SPI access
       send NOP command */
    SPI1_BUF = 0;
    /* write to SPI1_BUF register starts the SPI access */
    WAIT_SPI_IF

    /* get first byte of AL Event register */
    EscALEvent.Byte[1] = SPI1_BUF;
    /* reset SPI interrupt flag */
    SPI1_IF = 0;

    /* if the SPI transmission rate is higher than 15 MBaud, the Busy detection shall be
       done here */

    DESELECT_SPI
}


/////////////////////////////////////////////////////////////////////////////////////////
/**
 \param Address     EtherCAT ASIC address ( upper limit is 0x1FFF )    for access.
 \param Command    ESC_WR performs a write access; ESC_RD performs a read access.

 \brief The function addresses the EtherCAT ASIC via SPI for a following SPI access.
*////////////////////////////////////////////////////////////////////////////////////////
static void AddressingEsc( UINT16 Address, UINT8 Command )
{
    UBYTETOWORD tmp;
    VARVOLATILE UINT8 dummy;
    tmp.Word = ( Address << 3 ) | Command;
    /* select the SPI */
    SELECT_SPI;

    /* reset transmission flag */
    SPI1_IF=0;
    dummy = SPI1_BUF;
    /* there have to be at least 15 ns after the SPI1_SEL signal was active (0) before
       the transmission shall be started */
    /* send the first address/command byte to the ESC */
    SPI1_BUF = tmp.Byte[1];
    /* wait until the transmission of the byte is finished */
    WAIT_SPI_IF
    /* get first byte of AL Event register */

    EscALEvent.Byte[0] = SPI1_BUF;

    /* reset transmission flag */
    SPI1_IF=0;
    dummy = SPI1_BUF;
    /* send the second address/command byte to the ESC */
    SPI1_BUF = tmp.Byte[0];
    /* wait until the transmission of the byte is finished */
    WAIT_SPI_IF
    /* get second byte of AL Event register */

    EscALEvent.Byte[1] = SPI1_BUF;

    /* reset transmission flag */
    SPI1_IF = 0;

    /* if the SPI transmission rate is higher than 15 MBaud, the Busy detection shall be
       done here */
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \param Address     EtherCAT ASIC address ( upper limit is 0x1FFF )    for access.
 \param Command    ESC_WR performs a write access; ESC_RD performs a read access.

 \brief The function addresses the EtherCAT ASIC via SPI for a following SPI access.
        Shall be implemented if interrupts are supported else this function is equal to "AddressingEsc()"
*////////////////////////////////////////////////////////////////////////////////////////
static void ISR_AddressingEsc( UINT16 Address, UINT8 Command )
{
    VARVOLATILE UINT8 dummy;
    UBYTETOWORD tmp;
    tmp.Word = ( Address << 3 ) | Command;

    /* select the SPI */
    SELECT_SPI;

    /* reset transmission flag */
    SPI1_IF=0;

    /* there have to be at least 15 ns after the SPI1_SEL signal was active (0) before
       the transmission shall be started */
    /* send the first address/command byte to the ESC */
    SPI1_BUF = tmp.Byte[1];
    /* wait until the transmission of the byte is finished */
    WAIT_SPI_IF
    dummy = SPI1_BUF;
    /* reset transmission flag */
    SPI1_IF=0;

    /* send the second address/command byte to the ESC */
    SPI1_BUF = tmp.Byte[0];
    /* wait until the transmission of the byte is finished */
    WAIT_SPI_IF
    dummy = SPI1_BUF;

    /* reset transmission flag */
    SPI1_IF = 0;

    /* if the SPI transmission rate is higher than 15 MBaud, the Busy detection shall be
       done here */
}

/*--------------------------------------------------------------------------------------
------
------    exported hardware access functions
------
--------------------------------------------------------------------------------------*/


/////////////////////////////////////////////////////////////////////////////////////////
/**
\return     0 if initialization was successful

 \brief    This function intialize the Process Data Interface (PDI) and the host controller.
*////////////////////////////////////////////////////////////////////////////////////////
UINT8 HW_Init(void)
{
/*ECATCHANGE_START(V5.11) EL9800 2*/
    UINT32 intMask;
/*ECATCHANGE_END(V5.11) EL9800 2*/

    PORT_CFG;


      /* initialize the SPI registers for the ESC SPI */
    SPI1_CON1 = SPI1_CON1_VALUE;
    SPI1_STAT = SPI1_STAT_VALUE;


/*ECATCHANGE_START(V5.11) EL9800 2*/
    do
    {
        intMask = 0x93;
        HW_EscWriteDWord(intMask, ESC_AL_EVENTMASK_OFFSET);
        intMask = 0;
        HW_EscReadDWord(intMask, ESC_AL_EVENTMASK_OFFSET);
    } while (intMask != 0x93);

    intMask = 0x00;

    HW_EscWriteDWord(intMask, ESC_AL_EVENTMASK_OFFSET);

/*ECATCHANGE_END(V5.11) EL9800 2*/
    INIT_ESC_INT
    ENABLE_ESC_INT();

    INIT_SYNC0_INT
    INIT_SYNC1_INT

    ENABLE_SYNC0_INT;
    ENABLE_SYNC1_INT;

    INIT_ECAT_TIMER;
    START_ECAT_TIMER;

    /* enable all interrupts */
    ENABLE_GLOBAL_INT;

    return 0;
}


/////////////////////////////////////////////////////////////////////////////////////////
/**
 \brief    This function shall be implemented if hardware resources need to be release
        when the sample application stops
*////////////////////////////////////////////////////////////////////////////////////////
void HW_Release(void)
{

}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return    first two Bytes of ALEvent register (0x220)

 \brief  This function gets the current content of ALEvent register
*////////////////////////////////////////////////////////////////////////////////////////
UINT16 HW_GetALEventRegister(void)
{
    GetInterruptRegister();
    return EscALEvent.Word;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return    first two Bytes of ALEvent register (0x220)

 \brief  The SPI PDI requires an extra ESC read access functions from interrupts service routines.
        The behaviour is equal to "HW_GetALEventRegister()"
*////////////////////////////////////////////////////////////////////////////////////////
UINT16 HW_GetALEventRegister_Isr(void)
{
     ISR_GetInterruptRegister();
    return EscALEvent.Word;
}


/////////////////////////////////////////////////////////////////////////////////////////
/**
 \param pData        Pointer to a byte array which holds data to write or saves read data.
 \param Address     EtherCAT ASIC address ( upper limit is 0x1FFF )    for access.
 \param Len            Access size in Bytes.

 \brief  This function operates the SPI read access to the EtherCAT ASIC.
*////////////////////////////////////////////////////////////////////////////////////////
void HW_EscRead( MEM_ADDR *pData, UINT16 Address, UINT16 Len )
{
    /* HBu 24.01.06: if the SPI will be read by an interrupt routine too the
                     mailbox reading may be interrupted but an interrupted
                     reading will remain in a SPI transmission fault that will
                     reset the internal Sync Manager status. Therefore the reading
                     will be divided in 1-byte reads with disabled interrupt */
    UINT16 i = Len;
    UINT8 *pTmpData = (UINT8 *)pData;

    /* loop for all bytes to be read */
    while ( i-- > 0 )
    {
        /* the reading of data from the ESC can be interrupted by the
           AL Event ISR, in that case the address has to be reinitialized,
           in that case the status flag will indicate an error because
           the reading operation was interrupted without setting the last
           sent byte to 0xFF */
        DISABLE_AL_EVENT_INT;
         AddressingEsc( Address, ESC_RD );

        /* when reading the last byte the DI pin shall be 1 */
        SPI1_BUF = 0xFF;
        /* wait until transmission finished */
        WAIT_SPI_IF
        /* get data byte */
        *pTmpData++ = SPI1_BUF;
        /* enable the ESC interrupt to get the AL Event ISR the chance to interrupt,
           if the next byte is the last the transmission shall not be interrupted,
           otherwise a sync manager could unlock the buffer, because the last was
           read internally */
        ENABLE_AL_EVENT_INT;
        /* there has to be at least 15 ns + CLK/2 after the transmission is finished
           before the SPI1_SEL signal shall be 1 */
        DESELECT_SPI
        /* next address */
        Address++;
        /* reset transmission flag */
        SPI1_IF = 0;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \param pData        Pointer to a byte array which holds data to write or saves read data.
 \param Address     EtherCAT ASIC address ( upper limit is 0x1FFF )    for access.
 \param Len            Access size in Bytes.

\brief  The SPI PDI requires an extra ESC read access functions from interrupts service routines.
        The behaviour is equal to "HW_EscRead()"
*////////////////////////////////////////////////////////////////////////////////////////
void HW_EscReadIsr( MEM_ADDR *pData, UINT16 Address, UINT16 Len )
{
    UINT16 i = Len;
    UINT8 data = 0;

   UINT8 *pTmpData = (UINT8 *)pData;

    /* send the address and command to the ESC */
     ISR_AddressingEsc( Address, ESC_RD );
    /* loop for all bytes to be read */
    while ( i-- > 0 )
    {
        if ( i == 0 )
        {
            /* when reading the last byte the DI pin shall be 1 */
            data = 0xFF;
        }
        /* reset transmission flag */
        SPI1_IF = 0;

        /* start transmission */
        SPI1_BUF = data;
        /* wait until transmission finished */
        WAIT_SPI_IF
        /* get data byte */
        *pTmpData++ = SPI1_BUF;
    }
    /* reset transmission flag */
    SPI1_IF = 0;

    /* there has to be at least 15 ns + CLK/2 after the transmission is finished
       before the SPI1_SEL signal shall be 1 */
    DESELECT_SPI
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \param pData        Pointer to a byte array which holds data to write or saves write data.
 \param Address     EtherCAT ASIC address ( upper limit is 0x1FFF )    for access.
 \param Len            Access size in Bytes.

  \brief  This function operates the SPI write access to the EtherCAT ASIC.
*////////////////////////////////////////////////////////////////////////////////////////
void HW_EscWrite( MEM_ADDR *pData, UINT16 Address, UINT16 Len )
{
    UINT16 i = Len;
    VARVOLATILE UINT8 dummy;

    UINT8 *pTmpData = (UINT8 *)pData;

    /* loop for all bytes to be written */
    while ( i-- > 0 )
    {
        /* the reading of data from the ESC can be interrupted by the
           AL Event ISR, so every byte will be written separate */
        DISABLE_AL_EVENT_INT;
        /* HBu 24.01.06: wrong parameter ESC_RD */
         AddressingEsc( Address, ESC_WR );
        /* start transmission */
        SPI1_BUF = *pTmpData++;
        /* wait until transmission finished */
        WAIT_SPI_IF
        /* enable the ESC interrupt to get the AL Event ISR the chance to interrupt */
        /* SPI1_BUF must be read, otherwise the module will not transfer the next received data from SPIxSR to SPIxRXB.*/
        dummy = SPI1_BUF;
        ENABLE_AL_EVENT_INT;
        /* there has to be at least 15 ns + CLK/2 after the transmission is finished
           before the SPI1_SEL signal shall be 1 */

        DESELECT_SPI
        /* next address */
        Address++;
        /* reset transmission flag */
        SPI1_IF = 0;

    }
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \param pData        Pointer to a byte array which holds data to write or saves write data.
 \param Address     EtherCAT ASIC address ( upper limit is 0x1FFF )    for access.
 \param Len            Access size in Bytes.

 \brief  The SPI PDI requires an extra ESC write access functions from interrupts service routines.
        The behaviour is equal to "HW_EscWrite()"
*////////////////////////////////////////////////////////////////////////////////////////
void HW_EscWriteIsr( MEM_ADDR *pData, UINT16 Address, UINT16 Len )
{
    UINT16 i = Len;
    VARVOLATILE UINT16 dummy;
    UINT8 *pTmpData = (UINT8 *)pData;

    /* send the address and command to the ESC */
     ISR_AddressingEsc( Address, ESC_WR );
    /* loop for all bytes to be written */
    while ( i-- > 0 )
    {
        /* reset transmission flag */
        SPI1_IF = 0;

        /* start transmission */
        SPI1_BUF = *pTmpData;
        /* wait until transmission finished */
        WAIT_SPI_IF
        /* increment data pointer */
        dummy = SPI1_BUF;

        pTmpData++;
    }
    /* reset transmission flag */
    SPI1_IF = 0;

    /* there has to be at least 15 ns + CLK/2 after the transmission is finished
       before the SPI1_SEL signal shall be 1 */
    DESELECT_SPI
}




/////////////////////////////////////////////////////////////////////////////////////////
/**
 \brief    Interrupt service routine for the PDI interrupt from the EtherCAT Slave Controller
*////////////////////////////////////////////////////////////////////////////////////////

void __attribute__ ((__interrupt__, no_auto_psv)) EscIsr(void)
{
     PDI_Isr();

    /* reset the interrupt flag */
    ACK_ESC_INT;
}



/////////////////////////////////////////////////////////////////////////////////////////
/**
 \brief    Interrupt service routine for the interrupts from SYNC0
*////////////////////////////////////////////////////////////////////////////////////////
void __attribute__((__interrupt__, no_auto_psv)) Sync0Isr(void)
{
    Sync0_Isr();
    /* reset the interrupt flag */

    ACK_SYNC0_INT;
}
/////////////////////////////////////////////////////////////////////////////////////////
/**
 \brief    Interrupt service routine for the interrupts from SYNC1
*////////////////////////////////////////////////////////////////////////////////////////
void __attribute__((__interrupt__, no_auto_psv)) Sync1Isr(void)
{
    Sync1_Isr();
    /* reset the interrupt flag */

    ACK_SYNC1_INT;
}


/** @} */


