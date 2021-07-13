/*=======================================================================================
** File Name:  app_b_msg.h
**
** Title:  Message Definition Header File for APP_B Application
**
** $Author:    .
** $Revision: 1.1 $
** $Date:      2021-07-10
**
** Purpose:  To define APP_B's command and telemetry message defintions 
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2021-07-10 | . | Build #: Code Started
**
**=====================================================================================*/
    
#ifndef _APP_B_MSG_H_
#define _APP_B_MSG_H_

/*
** Pragmas
*/

/*
** Include Files
*/



/*
** Local Defines
*/

/*
** APP_B command codes
*/
#define APP_B_NOOP_CC                 0
#define APP_B_RESET_CC                1

/*
** Local Structure Declarations
*/
typedef struct
{
    uint8              TlmHeader[CFE_SB_TLM_HDR_SIZE];
    uint8              usCmdCnt;
    uint8              usCmdErrCnt;

    /* TODO:  Add declarations for additional housekeeping data here */

} APP_B_HkTlm_t;


#endif /* _APP_B_MSG_H_ */

/*=======================================================================================
** End of file app_b_msg.h
**=====================================================================================*/
    