/*=======================================================================================
** File Name:  app_a_private_types.h
**
** Title:  Type Header File for APP_A Application
**
** $Author:    Patrick Custer
** $Revision: 1.1 $
** $Date:      2021-07-12
**
** Purpose:  This header file contains declarations and definitions of all APP_A's private
**           data structures and data types.
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2021-07-12 | Patrick Custer | Build #: Code Started
**
**=====================================================================================*/
    
#ifndef _APP_A_PRIVATE_TYPES_H_
#define _APP_A_PRIVATE_TYPES_H_

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
} APP_A_NoArgCmd_t;


typedef struct
{
    uint32  counter;

    /* TODO:  Add input data to this application here, such as raw data read from I/O
    **        devices or data subscribed from other apps' output data.
    */

} APP_A_InData_t;

typedef struct
{
    uint8   ucTlmHeader[CFE_SB_TLM_HDR_SIZE];
    uint32  uiCounter;
} APP_A_OutData_t;

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

#endif /* _APP_A_PRIVATE_TYPES_H_ */

/*=======================================================================================
** End of file app_a_private_types.h
**=====================================================================================*/
    