/*=======================================================================================
** File Name:  app_a_msg.h
**
** Title:  Message Definition Header File for APP_A Application
**
** $Author:    Patrick Custer
** $Revision: 1.1 $
** $Date:      2021-07-12
**
** Purpose:  To define APP_A's command and telemetry message defintions 
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2021-07-12 | Patrick Custer | Build #: Code Started
**
**=====================================================================================*/
    
#ifndef _APP_A_MSG_H_
#define _APP_A_MSG_H_

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
** APP_A command codes
*/
#define APP_A_NOOP_CC                 0
#define APP_A_RESET_CC                1

/*
** The following enums map directly with app_a_msg since
** it is not importable 
*/
#define APP_A_DEC                     2
#define APP_A_INC                     3
#define APP_A_DEC_B                   4
#define APP_A_INC_B                   5
#define APP_A_RESET_COUNTER           6

/*
** Local Structure Declarations
*/
typedef struct
{
    uint8              TlmHeader[CFE_SB_TLM_HDR_SIZE];
    uint8              usCmdCnt;
    uint8              usCmdErrCnt;

    /* TODO:  Add declarations for additional housekeeping data here */
    uint32             counter;
} APP_A_HkTlm_t;


#endif /* _APP_A_MSG_H_ */

/*=======================================================================================
** End of file app_a_msg.h
**=====================================================================================*/
    