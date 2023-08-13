/**
* \addtogroup SSC-Device SSC-Device
* @{
*/

/**
\file SSC-DeviceObjects
\author ET9300Utilities.ApplicationHandler (Version 1.3.6.0) | EthercatSSC@beckhoff.com

\brief SSC-Device specific objects<br>
\brief NOTE : This file will be overwritten if a new object dictionary is generated!<br>
*/

#if defined(_SSC_DEVICE_) && (_SSC_DEVICE_ == 1)
#define PROTO
#else
#define PROTO extern
#endif
/******************************************************************************
*                    Object 0x1600 : DOChannels process data mapping
******************************************************************************/
/**
* \addtogroup 0x1600 0x1600 | DOChannels process data mapping
* @{
* \brief Object 0x1600 (DOChannels process data mapping) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x7000.1<br>
* SubIndex 2 - Reference to 0x7000.2<br>
* SubIndex 3 - Reference to 0x7000.3<br>
* SubIndex 4 - Padding entry (13Bit)<br>
* SubIndex 5 - Reference to 0x7000.5<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1600[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex1 - Reference to 0x7000.1 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex2 - Reference to 0x7000.2 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex3 - Reference to 0x7000.3 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex4 - Padding entry (13Bit) */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex5 - Reference to 0x7000.5 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1600[] = "DOChannels process data mapping\000"
"SubIndex 001\000"
"SubIndex 002\000"
"SubIndex 003\000"
"SubIndex 004\000"
"SubIndex 005\000\377";
#endif //#ifdef _OBJD_

#ifndef _SSC_DEVICE_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x7000.1 */
UINT32 SI2; /* Subindex2 - Reference to 0x7000.2 */
UINT32 SI3; /* Subindex3 - Reference to 0x7000.3 */
UINT32 SI4; /* Subindex4 - Padding entry (13Bit) */
UINT32 SI5; /* Subindex5 - Reference to 0x7000.5 */
} OBJ_STRUCT_PACKED_END
TOBJ1600;
#endif //#ifndef _SSC_DEVICE_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1600 DOChannelsProcessDataMapping0x1600
#if defined(_SSC_DEVICE_) && (_SSC_DEVICE_ == 1)
={5,0x70000101,0x70000201,0x70000301,0x0000000D,0x70000510}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1A00 : DIChannel process data mapping
******************************************************************************/
/**
* \addtogroup 0x1A00 0x1A00 | DIChannel process data mapping
* @{
* \brief Object 0x1A00 (DIChannel process data mapping) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Reference to 0x6000.1<br>
* SubIndex 2 - Reference to 0x6000.2<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1A00[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex1 - Reference to 0x6000.1 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex2 - Reference to 0x6000.2 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1A00[] = "DIChannel process data mapping\000"
"SubIndex 001\000"
"SubIndex 002\000\377";
#endif //#ifdef _OBJD_

#ifndef _SSC_DEVICE_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 - Reference to 0x6000.1 */
UINT32 SI2; /* Subindex2 - Reference to 0x6000.2 */
} OBJ_STRUCT_PACKED_END
TOBJ1A00;
#endif //#ifndef _SSC_DEVICE_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1A00 DIChannelProcessDataMapping0x1A00
#if defined(_SSC_DEVICE_) && (_SSC_DEVICE_ == 1)
={2,0x60000110,0x60000210}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1C12 : SyncManager 2 assignment
******************************************************************************/
/**
* \addtogroup 0x1C12 0x1C12 | SyncManager 2 assignment
* @{
* \brief Object 0x1C12 (SyncManager 2 assignment) definition
*/
#ifdef _OBJD_
/**
* \brief Entry descriptions<br>
* 
* Subindex 0<br>
* Subindex 1 - n (the same entry description is used)<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1C12[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ }};

/**
* \brief Object name definition<br>
* For Subindex 1 to n the syntax 'Subindex XXX' is used
*/
OBJCONST UCHAR OBJMEM aName0x1C12[] = "SyncManager 2 assignment\000\377";
#endif //#ifdef _OBJD_

#ifndef _SSC_DEVICE_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16   u16SubIndex0;  /**< \brief Subindex 0 */
UINT16 aEntries[1];  /**< \brief Subindex 1 - 1 */
} OBJ_STRUCT_PACKED_END
TOBJ1C12;
#endif //#ifndef _SSC_DEVICE_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1C12 sRxPDOassign
#if defined(_SSC_DEVICE_) && (_SSC_DEVICE_ == 1)
={1,{0x1600}}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1C13 : SyncManager 3 assignment
******************************************************************************/
/**
* \addtogroup 0x1C13 0x1C13 | SyncManager 3 assignment
* @{
* \brief Object 0x1C13 (SyncManager 3 assignment) definition
*/
#ifdef _OBJD_
/**
* \brief Entry descriptions<br>
* 
* Subindex 0<br>
* Subindex 1 - n (the same entry description is used)<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1C13[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ }};

/**
* \brief Object name definition<br>
* For Subindex 1 to n the syntax 'Subindex XXX' is used
*/
OBJCONST UCHAR OBJMEM aName0x1C13[] = "SyncManager 3 assignment\000\377";
#endif //#ifdef _OBJD_

#ifndef _SSC_DEVICE_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16   u16SubIndex0;  /**< \brief Subindex 0 */
UINT16 aEntries[1];  /**< \brief Subindex 1 - 1 */
} OBJ_STRUCT_PACKED_END
TOBJ1C13;
#endif //#ifndef _SSC_DEVICE_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1C13 sTxPDOassign
#if defined(_SSC_DEVICE_) && (_SSC_DEVICE_ == 1)
={1,{0x1A00}}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6000 : DIChannel
******************************************************************************/
/**
* \addtogroup 0x6000 0x6000 | DIChannel
* @{
* \brief Object 0x6000 (DIChannel) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - BTN<br>
* SubIndex 2 - ADCVal<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x6000[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex1 - BTN */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }}; /* Subindex2 - ADCVal */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x6000[] = "DIChannel\000"
"BTN\000"
"ADCVal\000\377";
#endif //#ifdef _OBJD_

#ifndef _SSC_DEVICE_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT16 BTN; /* Subindex1 - BTN */
UINT16 ADCVal; /* Subindex2 - ADCVal */
} OBJ_STRUCT_PACKED_END
TOBJ6000;
#endif //#ifndef _SSC_DEVICE_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ6000 DIChannel0x6000
#if defined(_SSC_DEVICE_) && (_SSC_DEVICE_ == 1)
={2,0,0}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x7000 : DOChannels
******************************************************************************/
/**
* \addtogroup 0x7000 0x7000 | DOChannels
* @{
* \brief Object 0x7000 (DOChannels) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - LED1<br>
* SubIndex 2 - LED2<br>
* SubIndex 3 - LED3<br>
* SubIndex 4<br>
* SubIndex 5 - DACVal<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x7000[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }, /* Subindex1 - LED1 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }, /* Subindex2 - LED2 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }, /* Subindex3 - LED3 */
{ DEFTYPE_NULL , 0xD , 0x0000 }, /* Subindex4 */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_RXPDOMAPPING }}; /* Subindex5 - DACVal */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x7000[] = "DOChannels\000"
"LED1\000"
"LED2\000"
"LED3\000"
"\000"
"DACVal\000\377";
#endif //#ifdef _OBJD_

#ifndef _SSC_DEVICE_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
BOOLEAN(LED1); /* Subindex1 - LED1 */
BOOLEAN(LED2); /* Subindex2 - LED2 */
BOOLEAN(LED3); /* Subindex3 - LED3 */
ALIGN13(SI4) /* Subindex4 */
UINT16 DACVal; /* Subindex5 - DACVal */
} OBJ_STRUCT_PACKED_END
TOBJ7000;
#endif //#ifndef _SSC_DEVICE_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ7000 DOChannels0x7000
#if defined(_SSC_DEVICE_) && (_SSC_DEVICE_ == 1)
={5,0,0,0,0,0}
#endif
;
/** @}*/







#ifdef _OBJD_
TOBJECT    OBJMEM ApplicationObjDic[] = {
/* Object 0x1600 */
{NULL , NULL ,  0x1600 , {DEFTYPE_PDOMAPPING , 5 | (OBJCODE_REC << 8)} , asEntryDesc0x1600 , aName0x1600 , &DOChannelsProcessDataMapping0x1600, NULL , NULL , 0x0000 },
/* Object 0x1A00 */
{NULL , NULL ,  0x1A00 , {DEFTYPE_PDOMAPPING , 2 | (OBJCODE_REC << 8)} , asEntryDesc0x1A00 , aName0x1A00 , &DIChannelProcessDataMapping0x1A00, NULL , NULL , 0x0000 },
/* Object 0x1C12 */
{NULL , NULL ,  0x1C12 , {DEFTYPE_UNSIGNED16 , 1 | (OBJCODE_ARR << 8)} , asEntryDesc0x1C12 , aName0x1C12 , &sRxPDOassign, NULL , NULL , 0x0000 },
/* Object 0x1C13 */
{NULL , NULL ,  0x1C13 , {DEFTYPE_UNSIGNED16 , 1 | (OBJCODE_ARR << 8)} , asEntryDesc0x1C13 , aName0x1C13 , &sTxPDOassign, NULL , NULL , 0x0000 },
/* Object 0x6000 */
{NULL , NULL ,  0x6000 , {DEFTYPE_RECORD , 2 | (OBJCODE_REC << 8)} , asEntryDesc0x6000 , aName0x6000 , &DIChannel0x6000, NULL , NULL , 0x0000 },
/* Object 0x7000 */
{NULL , NULL ,  0x7000 , {DEFTYPE_RECORD , 5 | (OBJCODE_REC << 8)} , asEntryDesc0x7000 , aName0x7000 , &DOChannels0x7000, NULL , NULL , 0x0000 },
{NULL,NULL, 0xFFFF, {0, 0}, NULL, NULL, NULL, NULL}};
#endif    //#ifdef _OBJD_
#undef PROTO

/** @}*/
#define _SSC_DEVICE_OBJECTS_H_
