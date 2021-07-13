/*=======================================================================================
** File Name:  app_b_private_types.h
**
** Title:  Type Header File for APP_B Application
**
** $Author:    .
** $Revision: 1.1 $
** $Date:      2021-07-10
**
** Purpose:  This header file contains declarations and definitions of all APP_B's private
**           data structures and data types.
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2021-07-10 | . | Build #: Code Started
**
**=====================================================================================*/
    
#ifndef _APP_B_PRIVATE_TYPES_H_
#define _APP_B_PRIVATE_TYPES_H_

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
} APP_B_NoArgCmd_t;


typedef struct
{
    uint32  counter;

    /* TODO:  Add input data to this application here, such as raw data read from I/O
    **        devices or data subscribed from other apps' output data.
    */

} APP_B_InData_t;

typedef struct
{
    uint8   ucTlmHeader[CFE_SB_TLM_HDR_SIZE];
    uint32  uiCounter;
} APP_B_OutData_t;

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

#endif /* _APP_B_PRIVATE_TYPES_H_ */

/*=======================================================================================
** End of file app_b_private_types.h
**=====================================================================================*/
    