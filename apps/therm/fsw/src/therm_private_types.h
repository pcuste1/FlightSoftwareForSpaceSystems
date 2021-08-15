/*=======================================================================================
** File Name:  therm_private_types.h
**
** Title:  Type Header File for THERM Application
**
** $Author:    Runtime Terror
** $Revision: 1.1 $
** $Date:      2021-08-14
**
** Purpose:  This header file contains declarations and definitions of all THERM's private
**           data structures and data types.
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2021-08-14 | Runtime Terror | Build #: Code Started
**
**=====================================================================================*/
    
#ifndef _THERM_PRIVATE_TYPES_H_
#define _THERM_PRIVATE_TYPES_H_

/*
** Pragmas
*/

/*
** Include Files
*/
#include "cfe.h"

/*
** Local Defines
*/

/*
** Local Structure Declarations
*/

typedef struct
{
    uint8  ucCmdHeader[CFE_SB_CMD_HDR_SIZE];
} THERM_NoArgCmd_t;


typedef struct
{
    uint32  counter;

    /* TODO:  Add input data to this application here, such as raw data read from I/O
    **        devices or data subscribed from other apps' output data.
    */
    uint16			    wiseSbcState;
    uint16				wiseDamage;
    uint16				wiseActiveCap;
    uint16				wiseCapA_State;
    uint16				wiseCapA_Charge;
    uint16				wiseCapB_State;
    uint16				wiseCapB_Charge;
    uint16				wiseCapC_State;
    uint16				wiseCapC_Charge;
    uint16				wiseHtrA_State;
    uint16				wiseHtrB_State;
    uint16				wiseLvrA_State;
    uint16				wiseLvrB_State;
    uint16              wiseSSR_Count;
    int16				wiseTemp;

} THERM_InData_t;

typedef struct
{
    uint8   ucTlmHeader[CFE_SB_TLM_HDR_SIZE];
    uint32  uiCounter;
} THERM_OutData_t;

/* TODO:  Add more private structure definitions here, if necessary. */

/*
** External Global Variables
*/

/*
** Global Variables
*/

/*
** Local Variables
*/

/*
** Local Function Prototypes
*/

#endif /* _THERM_PRIVATE_TYPES_H_ */

/*=======================================================================================
** End of file therm_private_types.h
**=====================================================================================*/
    